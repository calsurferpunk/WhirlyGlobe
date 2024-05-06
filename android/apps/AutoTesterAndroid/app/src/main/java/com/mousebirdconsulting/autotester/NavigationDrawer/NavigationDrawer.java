package com.mousebirdconsulting.autotester.NavigationDrawer;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Build;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.mousebirdconsulting.autotester.ConfigOptions;
import com.mousebirdconsulting.autotester.R;

public class NavigationDrawer extends LinearLayout {

	public boolean seeView = false;
	private TextView runMapView, runGlobeView, runBothView, seeViewView, interactiveMode, multilpleMode, singleMode, selectAllAction, deselectAllAction, optionsSection, actionSection;
	private View separator_1, separator_2;

	public NavigationDrawer(Context context) {
		this(context, null);
	}

	public NavigationDrawer(Context context, AttributeSet attrs) {
		super(context, attrs);

		setOrientation(VERTICAL);

		TypedValue typedValue = new TypedValue();
		context.getTheme().resolveAttribute(android.R.attr.windowBackground, typedValue, true);
		setBackgroundColor(typedValue.data);

		LayoutInflater.from(context).inflate(R.layout.view_navigation_drawer, this, true);

		runGlobeView = findViewById(R.id.runGlobe);
		runBothView = findViewById(R.id.runBoth);
		runMapView = findViewById(R.id.runMap);
		seeViewView = findViewById(R.id.seeView);
		interactiveMode = findViewById(R.id.runInteractive);
		multilpleMode = findViewById(R.id.runMultiple);
		singleMode = findViewById(R.id.runSingle);
		selectAllAction = findViewById(R.id.selectAll);
		deselectAllAction = findViewById(R.id.deselectAll);
		optionsSection = findViewById(R.id.optionsSection);
		actionSection = findViewById(R.id.actionSection);
		separator_1 = findViewById(R.id.separator_1);
		separator_2 = findViewById(R.id.separator_2);
	}

//	@OnClick({R.id.runMap, R.id.runGlobe, R.id.runBoth, R.id.seeView, R.id.runInteractive, R.id.runMultiple, R.id.runSingle, R.id.selectAll, R.id.deselectAll})
	void onItemClick(View view) {
		if (getContext() instanceof Listener) {
			((Listener) getContext()).onItemClick(view.getId());
		}
	}

	public void setSelectedItemId(int itemId) {

        switch (itemId) {
            case R.id.runMap:
                deselectView(runBothView);
                deselectView(runGlobeView);
                selectView(runMapView);
                ConfigOptions.setTestType(getContext(), ConfigOptions.TestType.MapTest);
                break;
            case R.id.runGlobe:
                deselectView(runBothView);
                deselectView(runMapView);
                selectView(runGlobeView);
                ConfigOptions.setTestType(getContext(), ConfigOptions.TestType.GlobeTest);
                break;
            case R.id.runBoth:
                deselectView(runMapView);
                deselectView(runGlobeView);
                selectView(runBothView);
                ConfigOptions.setTestType(getContext(), ConfigOptions.TestType.BothTest);
                break;
            case R.id.seeView:
                if (!seeView) {
                    selectView(seeViewView);
                    ConfigOptions.setViewSetting(getContext(), ConfigOptions.ViewMapOption.ViewMap);
                    seeView = true;
                } else {
                    seeView = false;
                    deselectView(seeViewView);
                    ConfigOptions.setViewSetting(getContext(), ConfigOptions.ViewMapOption.None);
                }
                break;
            case R.id.runInteractive:
                deselectView(multilpleMode);
                deselectView(singleMode);
                selectView(interactiveMode);
                hideOptions(TextView.INVISIBLE);
                ConfigOptions.setExecutionMode(getContext(), ConfigOptions.ExecutionMode.Interactive);
                break;
            case R.id.runMultiple:
                selectView(multilpleMode);
                deselectView(singleMode);
                deselectView(interactiveMode);
                hideOptions(TextView.VISIBLE);
                ConfigOptions.setExecutionMode(getContext(), ConfigOptions.ExecutionMode.Multiple);
                break;
            case R.id.runSingle:
                deselectView(multilpleMode);
                selectView(singleMode);
                deselectView(interactiveMode);
                hideOptions(TextView.VISIBLE);
                hideActions(INVISIBLE);
                ConfigOptions.setExecutionMode(getContext(), ConfigOptions.ExecutionMode.Single);
                break;
        }
    }

	private void hideOptions (int visibility){

		optionsSection.setVisibility(visibility);
		actionSection.setVisibility(visibility);
		runBothView.setVisibility(visibility);
		runGlobeView.setVisibility(visibility);
		runBothView.setVisibility(visibility);
		selectAllAction.setVisibility(visibility);
		deselectAllAction.setVisibility(visibility);
		runMapView.setVisibility(visibility);
		seeViewView.setVisibility(visibility);
		separator_1.setVisibility(visibility);
		separator_2.setVisibility(visibility);
	}

	private void hideActions(int visibility){
		actionSection.setVisibility(visibility);
		selectAllAction.setVisibility(visibility);
		deselectAllAction.setVisibility(visibility);
		separator_2.setVisibility(visibility);
	}

	private void deselectView(TextView view) {
        view.getCompoundDrawables()[0].setTintList(null);
        view.setTypeface(null, Typeface.NORMAL);
    }

	private void selectView(TextView view) {
        view.getCompoundDrawables()[0].setTint(Color.BLACK);
		view.setTypeface(null, Typeface.BOLD);
	}

	public void getUserPreferences() {

		switch (ConfigOptions.getTestType(getContext())) {
			case MapTest:
				setSelectedItemId(R.id.runMap);
				break;
			case BothTest:
				setSelectedItemId(R.id.runBoth);
				break;
			case GlobeTest:
				setSelectedItemId(R.id.runGlobe);
				break;
		}

		switch (ConfigOptions.getExecutionMode(getContext())){
			case Interactive:
				setSelectedItemId(R.id.runInteractive);
				hideOptions(TextView.INVISIBLE);
				break;
			case Multiple:
				setSelectedItemId(R.id.runMultiple);
				hideOptions(TextView.VISIBLE);
				break;
			case Single:
				setSelectedItemId(R.id.runSingle);
				hideOptions(TextView.VISIBLE);
				hideActions(INVISIBLE);
				break;
		}

		switch (ConfigOptions.getViewSetting(getContext())) {
			case None:
				seeView = true;
				break;
			case ViewMap:
				seeView = false;
				break;
		}
		setSelectedItemId(R.id.seeView);
	}

	public interface Listener {
		void onItemClick(int itemId);
	}
}
