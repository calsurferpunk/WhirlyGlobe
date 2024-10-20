package com.mousebird.maply.sld.sldsymbolizers;

import com.mousebird.maply.RenderControllerInterface;
import com.mousebird.maply.VectorStyleSettings;
import com.mousebird.maply.sld.sldstyleset.AssetWrapper;

import java.lang.ref.WeakReference;
import java.net.URL;
import java.util.HashMap;


public class SLDSymbolizerParams {

    // Assigned once per SLD
    private WeakReference<RenderControllerInterface> baseController;
    private VectorStyleSettings vectorStyleSettings;
    private AssetWrapper assetWrapper;
    private String basePath;

    public RenderControllerInterface getBaseController() {
        return baseController.get();
    }
    public VectorStyleSettings getVectorStyleSettings() {
        return vectorStyleSettings;
    }
    public AssetWrapper getAssetWrapper() {
        return assetWrapper;
    }
    public String getBasePath() {
        return basePath;
    }


    public SLDSymbolizerParams(RenderControllerInterface baseController, AssetWrapper assetWrapper, VectorStyleSettings vectorStyleSettings, String basePath, int relativeDrawPriority) {
        this.baseController = new WeakReference<>(baseController);
        this.assetWrapper = assetWrapper;
        this.vectorStyleSettings = vectorStyleSettings;
        this.basePath = basePath;
        this.relativeDrawPriority = relativeDrawPriority;
    }


    // Assigned once per Rule
    private Number minScaleDenominator;
    private Number maxScaleDenominator;
    private HashMap<String, Object> crossSymbolizerParams;

    public void resetRuleParams() {
        this.minScaleDenominator = null;
        this.maxScaleDenominator = null;
        crossSymbolizerParams = new HashMap<>();
    }

    public Number getMinScaleDenominator() {
        return minScaleDenominator;
    }
    public void setMinScaleDenominator(Number minScaleDenominator) {
        this.minScaleDenominator = minScaleDenominator;
    }

    public Number getMaxScaleDenominator() {
        return maxScaleDenominator;
    }
    public void setMaxScaleDenominator(Number maxScaleDenominator) {
        this.maxScaleDenominator = maxScaleDenominator;
    }

    public HashMap<String, Object> getCrossSymbolizerParams() {
        return crossSymbolizerParams;
    }



    // Increments once per Symbolizer
    private int relativeDrawPriority;

    public int getRelativeDrawPriority() {
        return relativeDrawPriority;
    }

    public void setRelativeDrawPriority(int relativeDrawPriority) {
        this.relativeDrawPriority = relativeDrawPriority;
    }

    public void incrementRelativeDrawPriority() {
        relativeDrawPriority = relativeDrawPriority + 1;
    }

}
