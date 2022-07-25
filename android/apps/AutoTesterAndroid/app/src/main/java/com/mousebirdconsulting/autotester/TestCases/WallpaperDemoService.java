package com.mousebirdconsulting.autotester.TestCases;

import android.opengl.GLSurfaceView;
import android.service.wallpaper.WallpaperService;
import android.view.MotionEvent;
import android.view.SurfaceHolder;

import com.mousebird.maply.GlobeController;
import com.mousebird.maply.QuadImageLoader;
import com.mousebird.maply.RemoteTileInfoNew;
import com.mousebird.maply.SamplingParams;
import com.mousebird.maply.SphericalMercatorCoordSystem;

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
        private WallpaperDemoSurfaceView wallpaperView;
        private QuadImageLoader imageLoader;

        @Override
        public void onCreate(SurfaceHolder surfaceHolder)
        {
            super.onCreate(surfaceHolder);

            File cacheDir = new File(WallpaperDemoService.this.getCacheDir(), "stamen_watercolor6");
            SamplingParams params;
            RemoteTileInfoNew tileInfo;
            GlobeController globeController;
            GlobeController.Settings globeSettings = new GlobeController.Settings();

            wallpaperView = new WallpaperDemoSurfaceView();
            globeSettings.loadLibraryName = loadLibraryName();
            globeController = new GlobeController(WallpaperDemoService.this, wallpaperView, globeSettings);
            globeController.setKeepNorthUp(true);

            tileInfo = new RemoteTileInfoNew("http://tile.stamen.com/watercolor/{z}/{x}/{y}.png", 0, 18);
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

        /**
         * Override this if you've got a different name for the core WG-Maply library.
         */
        public String loadLibraryName() {
            return "whirlyglobemaply";
        }
    }

    private class WallpaperDemoSurfaceView extends GLSurfaceView
    {
        private SurfaceHolder surfaceHolder;

        public WallpaperDemoSurfaceView()
        {
            super(WallpaperDemoService.this);
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
    }
}
