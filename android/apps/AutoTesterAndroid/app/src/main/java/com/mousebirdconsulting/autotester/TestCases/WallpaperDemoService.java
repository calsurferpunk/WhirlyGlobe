package com.mousebirdconsulting.autotester.TestCases;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.service.wallpaper.WallpaperService;
import android.view.MotionEvent;
import android.view.SurfaceHolder;

import com.mousebird.maply.GlobeController;
import com.mousebird.maply.QuadImageLoader;
import com.mousebird.maply.RemoteTileInfoNew;
import com.mousebird.maply.SamplingParams;
import com.mousebird.maply.SphericalMercatorCoordSystem;
import com.mousebirdconsulting.autotester.R;

import java.io.File;

public class WallpaperDemoService extends WallpaperService
{
    private Engine wallpaperEngine;

    @Override
    public Engine onCreateEngine()
    {
        wallpaperEngine = new WallpaperDemoEngine();
        return(wallpaperEngine);
    }

    private class WallpaperDemoEngine extends Engine
    {
        private class WallpaperDemoSurfaceView extends GLSurfaceView
        {
            private boolean haveRenderer = false;
            private SurfaceHolder surfaceHolder;

            public WallpaperDemoSurfaceView(Context context)
            {
                super(context);
                setPreserveEGLContextOnPause(true);
            }

            @Override
            public SurfaceHolder getHolder()
            {
                if(surfaceHolder == null)
                {
                    surfaceHolder = wallpaperEngine.getSurfaceHolder();
                }
                return(surfaceHolder);
            }

            public void onDestroy()
            {
                super.onDetachedFromWindow();
            }

            @Override
            public void setRenderer(Renderer renderer)
            {
                super.setRenderer(renderer);
                haveRenderer = true;
            }

            public boolean getHaveRenderer()
            {
                return(haveRenderer);
            }
        }

        private WallpaperDemoSurfaceView wallpaperView;
        private QuadImageLoader imageLoader;

        @Override
        public void onCreate(SurfaceHolder surfaceHolder)
        {
            super.onCreate(surfaceHolder);

            File cacheDir = new File(WallpaperDemoService.this.getCacheDir(), "stamen_watercolor6");
            String stamenKey = getString(R.string.stamen_map_key);
            SamplingParams params;
            RemoteTileInfoNew tileInfo;
            GlobeController globeController;
            GlobeController.Settings globeSettings = new GlobeController.Settings();

            wallpaperView = new WallpaperDemoSurfaceView(WallpaperDemoService.this);
            globeSettings.loadLibraryName = loadLibraryName();
            globeController = new GlobeController(WallpaperDemoService.this, wallpaperView, globeSettings);
            globeController.setKeepNorthUp(true);

            tileInfo = new RemoteTileInfoNew("https://tiles.stadiamaps.com/tiles/stamen_terrain_background/{z}/{x}/{y}@2x.png?api_key=" + stamenKey, 0, 18);
            tileInfo.cacheDir = cacheDir;

            params = new SamplingParams();
            params.setCoordSystem(new SphericalMercatorCoordSystem());
            params.setCoverPoles(true);
            params.setEdgeMatching(true);
            params.setMinZoom(tileInfo.minZoom);
            params.setMaxZoom(tileInfo.maxZoom);
            params.setSingleLevel(true);
            imageLoader = new QuadImageLoader(params, tileInfo, globeController);

            setTouchEventsEnabled(true);
        }

        @Override
        public void onDestroy()
        {
            super.onDestroy();
            wallpaperView.onDestroy();
            wallpaperView = null;

            if(imageLoader != null)
            {
                imageLoader.shutdown();
            }
            imageLoader = null;
        }

        @Override
        public void onTouchEvent(MotionEvent event)
        {

            wallpaperView.onTouchEvent(event);
        }

        @Override
        public void onVisibilityChanged(boolean visible)
        {
            super.onVisibilityChanged(visible);

            if(wallpaperView != null && wallpaperView.getHaveRenderer())
            {
                if(visible)
                {
                    wallpaperView.onResume();
                    wallpaperView.requestRender();
                }
                else
                {
                    wallpaperView.onPause();
                }
            }
        }

        /**
         * Override this if you've got a different name for the core WG-Maply library.
         */
        public String loadLibraryName() {
            return "whirlyglobemaply";
        }
    }
}
