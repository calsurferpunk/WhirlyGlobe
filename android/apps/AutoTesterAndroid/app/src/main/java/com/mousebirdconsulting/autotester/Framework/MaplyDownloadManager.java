package com.mousebirdconsulting.autotester.Framework;

import android.app.Activity;
import android.os.AsyncTask;

import com.mousebirdconsulting.autotester.ConfigOptions;

import java.lang.ref.WeakReference;
import java.util.ArrayList;


public class MaplyDownloadManager extends AsyncTask<Void, Void, Void> {

	protected ArrayList<MaplyTestCase> testCases;
	protected MaplyDownloadManagerListener listener;
	protected WeakReference<Activity> activityReference;

	public interface MaplyDownloadManagerListener {
		void onFinish();
		void onTestFinished(MaplyTestCase testCase);
	}

	public MaplyDownloadManager(Activity activity, ArrayList<MaplyTestCase> testCases, MaplyDownloadManagerListener listener) {
		this.testCases = testCases;
		this.listener = listener;
		this.activityReference = new WeakReference<>(activity);
	}

	@Override
	protected void onPreExecute() {
		super.onPreExecute();
	}

	@Override
	protected Void doInBackground(Void... params) {
		for (final MaplyTestCase testCase: this.testCases) {
			Activity activity = activityReference.get();

			if (testCase.areResourcesDownloaded()) {
				// already downloaded by previous tests
				ConfigOptions.setTestState(activity, testCase.getTestName(),  ConfigOptions.TestState.Ready);

			} else {
				ConfigOptions.setTestState(activity, testCase.getTestName(), ConfigOptions.TestState.Downloading);

				testCase.downloadResources();

				if (ConfigOptions.getTestState(activity, testCase.getTestName()) != ConfigOptions.TestState.Error) {
					ConfigOptions.setTestState(activity, testCase.getTestName(),  ConfigOptions.TestState.Ready);
				}
			}
			activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					listener.onTestFinished(testCase);
				}
			});
		}
		return null;
	}

	@Override
	protected void onPostExecute(Void aVoid) {
		super.onPostExecute(aVoid);
		if (listener != null){
			listener.onFinish();
		}
	}
}
