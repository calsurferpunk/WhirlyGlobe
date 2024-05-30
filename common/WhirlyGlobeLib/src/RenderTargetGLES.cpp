/*  RenderTargetGLES.cpp
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 5/13/19.
 *  Copyright 2011-2023 mousebird consulting
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#import "RenderTargetGLES.h"
#import "TextureGLES.h"
#import "UtilsGLES.h"
#import "WhirlyKitLog.h"

namespace WhirlyKit
{

RenderTargetGLES::RenderTargetGLES()
{
    init();
}

RenderTargetGLES::RenderTargetGLES(SimpleIdentity newID) :
    RenderTargetSettings(newID)
{
    init();
}

void RenderTargetGLES::init()
{
    RenderTarget::init();
}

// Whether to use clear color or value
// todo: is there a gl*() function for this?
static bool isColorTargetFormat(TextureType tt)
{
    switch (tt)
    {
        case TexTypeUnsignedByte:
        case TexTypeShort565:
        case TexTypeShort4444:
        case TexTypeShort5551:      return true;
        case TexTypeSingleChannel:
        case TexTypeDoubleChannel:
        case TexTypeSingleFloat16:
        case TexTypeSingleFloat32:
        case TexTypeDoubleFloat16:
        case TexTypeDoubleFloat32:
        case TexTypeQuadFloat16:
        case TexTypeQuadFloat32:
        case TexTypeDepthFloat32:
        case TexTypeSingleInt16:
        case TexTypeSingleUInt16:
        case TexTypeDoubleUInt16:
        case TexTypeSingleUInt32:
        case TexTypeDoubleUInt32:
        case TexTypeQuadUInt32:     return false;
        default:                    return true;
    }
}

bool RenderTargetGLES::init(SceneRenderer *inRenderer,Scene *scene,SimpleIdentity targetTexID)
{
    auto *renderer = (SceneRendererGLES *)inRenderer;
    
    if (framebuffer == 0)
    {
        glGenFramebuffers(1, &framebuffer);
    }
    
    // Our destination is a texture in this case
    if (targetTexID)
    {
        colorbuffer = 0;
        setTargetTexture(inRenderer,scene,targetTexID);
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        
        // Generate our own color buffer
        if (colorbuffer == 0)
            glGenRenderbuffers(1, &colorbuffer);
        CheckGLError("RenderTarget: glGenRenderbuffers");
        glBindRenderbuffer(GL_RENDERBUFFER, colorbuffer);
        CheckGLError("RenderTarget: glBindRenderbuffer");
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorbuffer);
        CheckGLError("RenderTarget: glFramebufferRenderbuffer");
        
        renderer->defaultTargetInit(this);
        
        if (depthbuffer == 0)
            glGenRenderbuffers(1, &depthbuffer);
        CheckGLError("RenderTarget: glGenRenderbuffers");
        glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
        CheckGLError("RenderTarget: glBindRenderbuffer");
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
        CheckGLError("RenderTarget: glRenderbufferStorage");
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);
        CheckGLError("RenderTarget: glFramebufferRenderbuffer");
        
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER) ;
        if(status != GL_FRAMEBUFFER_COMPLETE) {
            wkLogLevel(Error,"Failed to build valid render target: %x", status);
            return false;
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        CheckGLError("RenderTarget: glBindFramebuffer");
    }
    
    isSetup = false;
    return true;
}
    
bool RenderTargetGLES::setTargetTexture(SceneRenderer *sceneRender,Scene *scene,SimpleIdentity targetTexID)
{
    if (TextureBaseRef tex = scene->getTexture(targetTexID))
    {
        setTargetTexture(tex.get());
        return true;
    }
    return false;
}

void RenderTargetGLES::setTargetTexture(TextureBase *inTex)
{
    auto *tex = dynamic_cast<TextureBaseGLES *>(inTex);
    if (!tex)
        return;

    texId = tex->getId();

    if (framebuffer == 0) {
        glGenFramebuffers(1, &framebuffer);
        colorbuffer = 0;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->getGLId(), 0);
    CheckGLError("RenderTarget: glFramebufferTexture2D");
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (const auto glTex = dynamic_cast<const TextureGLES *>(tex))
    {
        isColorTarget = isColorTargetFormat(glTex->getFormat());
    }
    else
    {
        wkLogLevel(Warn, "TextureBaseGLES is not a TextureGLES");
    }
}

RawDataRef RenderTargetGLES::snapshot()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    CheckGLError("SceneRendererES2: glBindFramebuffer");
    glViewport(0, 0, width, height);
    CheckGLError("SceneRendererES2: glViewport");
    
    // Note: We're just assuming this format from the texture.  Should check
    uint32_t len = width * height * sizeof(GLubyte) * 4;
    auto* pixels = (GLubyte*) malloc(len);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    CheckGLError("RenderTargetGLES::snapshot: glReadPixels");
    
    auto rawData = RawDataRef(new RawDataWrapper(pixels,len,true));
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    return rawData;
}
    
RawDataRef RenderTargetGLES::snapshot(int startX,int startY,int snapWidth,int snapHeight)
{
    if (snapWidth == 0 || snapHeight == 0)
        return {};
    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    CheckGLError("SceneRendererES2: glBindFramebuffer");
    glViewport(0, 0, snapWidth, snapHeight);
    CheckGLError("SceneRendererES2: glViewport");
    
    // Note: We're just assuming this format from the texture.  Should check
    uint32_t len = snapWidth * snapHeight * sizeof(GLubyte) * 4;
    auto* pixels = (GLubyte*) malloc(len);
    glReadPixels(startX, startY, snapWidth, snapHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    auto rawData = RawDataRef(new RawDataWrapper(pixels,len,true));

    return rawData;
}

bool RenderTargetGLES::initFromState(int inWidth,int inHeight)
{
    width = inWidth;
    height = inHeight;
    GLint iVal;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING,&iVal);    framebuffer = iVal;
    glGetIntegerv(GL_RENDERBUFFER_BINDING,&iVal);   colorbuffer = iVal;
    
    //    wkLogLevel(Debug,"RenderTarget initFromState: framebuffer = %d colorbuffer = %d width = %d, height = %d",framebuffer,colorbuffer,width,height);
    
    return true;
}

void RenderTargetGLES::clear()
{
    if (colorbuffer)
        glDeleteRenderbuffers(1,&colorbuffer);
    if (depthbuffer)
        glDeleteRenderbuffers(1,&depthbuffer);
    if (framebuffer)
        glDeleteFramebuffers(1,&framebuffer);
}

void RenderTargetGLES::setActiveFramebuffer(SceneRendererGLES *renderer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    CheckGLError("RenderTarget::setActiveFramebuffer: glBindFramebuffer");
    glViewport(0, 0, width, height);
    CheckGLError("RenderTarget::setActiveFramebuffer: glViewport");
    if (colorbuffer) {
        glBindRenderbuffer(GL_RENDERBUFFER, colorbuffer);
        CheckGLError("RenderTarget::setActiveFramebuffer: glBindRenderbuffer");
    }
    
    // Note: Have to run this all the time for some reason
    //    if (!isSetup)
    {
        if (blendEnable)
        {
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }

        if (isColorTarget)
        {
            glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        }
        else
        {
            glClearColor(clearVal, clearVal, clearVal, clearVal);
        }

        CheckGLError("RenderTarget::setActiveFramebuffer: glClearColor");
        isSetup = true;
    }
}
    
}
