package com.mousebirdconsulting.autotester;

import android.content.Intent;
import android.os.Bundle;
import android.os.Debug;

import androidx.core.content.res.ResourcesCompat;
import androidx.fragment.app.Fragment;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.os.Handler;

import com.mousebirdconsulting.autotester.Fragments.TestListFragment;
import com.mousebirdconsulting.autotester.Fragments.ViewTestFragment;
import com.mousebirdconsulting.autotester.Framework.MaplyTestCase;
import com.mousebirdconsulting.autotester.Framework.MaplyTestResult;
import com.mousebirdconsulting.autotester.NavigationDrawer.NavigationDrawer;

import java.io.File;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Objects;

public class MainActivity extends AppCompatActivity implements NavigationDrawer.Listener {

	Toolbar toolbar;
	DrawerLayout drawerLayout; //Drawerlayout
	NavigationDrawer navigationDrawer;
	private Menu menu;
	private TestListFragment testList;
	private ViewTestFragment viewTest;
	private MaplyTestCase interactiveTest = null;

	private boolean cancelled = false;
	private boolean executing = false;

	private ArrayList<MaplyTestResult> testResults;

	Handler memHandler = new Handler();
	private Runnable runnableCode = new Runnable() {
		@Override
		public void run() {
			dumpMemory();
			memHandler.postDelayed(runnableCode, 2000);
		}
	};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
//		System.loadLibrary("gnustl_shared");

		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_main);
		toolbar = findViewById(R.id.toolbar);
		drawerLayout = findViewById(R.id.drawer_layout);
		navigationDrawer = findViewById(R.id.navigation_drawer);

		// Force a load of the library
		System.loadLibrary("whirlyglobemaply");

		//Create toolbar
		configureToolbar();
		configureNavigationDrawer();
		deleteRecursive(ConfigOptions.getCacheDir(this));
		this.navigationDrawer.getUserPreferences();
		this.testList = new TestListFragment();
		this.testResults = new ArrayList<>();
		this.viewTest = new ViewTestFragment();

		memHandler.post(runnableCode);
	}

	// Code courtesy: http://stackoverflow.com/questions/3238388/android-out-of-memory-exception-in-gallery/3238945#3238945
	void dumpMemory()
	{
		Double allocated = (double)Debug.getNativeHeapAllocatedSize() /1048576.0;
		Double available = (double)Debug.getNativeHeapSize() /1048576.0;
		Double free = (double)Debug.getNativeHeapFreeSize() /1048576.0;
		DecimalFormat df = new DecimalFormat();
		df.setMaximumFractionDigits(2);
		df.setMinimumFractionDigits(2);

		Log.d("maply", "heap native: allocated " + df.format(allocated) + "MB of " + df.format(available) + "MB (" + df.format(free) + "MB free)");
		Log.d("maply", "memory: allocated: " + df.format(Double.valueOf(Runtime.getRuntime().totalMemory()/1048576.0)) + "MB of " + df.format(Double.valueOf(Runtime.getRuntime().maxMemory()/1048576.0))+ "MB (" + df.format(Double.valueOf(Runtime.getRuntime().freeMemory()/1048576.0)) +"MB free)");
	}

	void deleteRecursive(File fileOrDirectory) {
		if (fileOrDirectory.isDirectory())
			for (File child : Objects.requireNonNull(Objects.requireNonNull(fileOrDirectory.listFiles())))
				deleteRecursive(child);

		fileOrDirectory.delete();
	}

	@Override
	protected void onResume() {
		super.onResume();

		this.navigationDrawer.getUserPreferences();
		this.testList = new TestListFragment();
		this.testList.downloadResources(this);
		selectFragment(this.testList);
		this.viewTest = new ViewTestFragment();
	}

	private void configureToolbar() {
		setSupportActionBar(toolbar);

		//Add home button
		androidx.appcompat.app.ActionBar actionBar = getSupportActionBar();
		if (actionBar != null) {
			actionBar.setDisplayHomeAsUpEnabled(true);
			actionBar.setDisplayShowTitleEnabled(true);
			actionBar.setHomeAsUpIndicator(R.drawable.ic_options_action);
		}
	}

	private void configureNavigationDrawer() {
		this.drawerLayout.setDrawerShadow(R.drawable.drawer_shadow, GravityCompat.START);
		drawerLayout.setDrawerLockMode(DrawerLayout.LOCK_MODE_LOCKED_CLOSED);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.menu_main, menu);
		this.menu = menu;
		selectFragment(this.testList);
		this.testList.downloadResources(this);
		showOverflowMenu(ConfigOptions.getExecutionMode(getApplicationContext())== ConfigOptions.ExecutionMode.Multiple);
		return true;
	}

	public void showOverflowMenu(boolean showMenu){
		if(menu == null)
			return;
		menu.setGroupVisible(R.id.main_menu_group, showMenu);
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();

		switch (id) {
			case android.R.id.home:
				if (!executing) {
					drawerLayout.openDrawer(GravityCompat.START);
				}
				break;
			case R.id.playTests:
				if (ConfigOptions.getExecutionMode(getApplicationContext()) == ConfigOptions.ExecutionMode.Interactive) {
					finalizeInteractiveTest();
				}
				if (ConfigOptions.getExecutionMode(getApplicationContext()) == ConfigOptions.ExecutionMode.Multiple) {
					if (!executing) {
						this.runTests();
					} else {
						this.stopTests();
					}
				}
				break;
		}
		return super.onOptionsItemSelected(item);
	}

	private void selectFragment(Fragment fragment) {
		this.drawerLayout.closeDrawer(GravityCompat.START);

		getSupportFragmentManager()
			.beginTransaction()
			.replace(R.id.content_frame, fragment)
			.commit();
	}

	public void prepareTest(MaplyTestCase testCase) {
		ConfigOptions.TestState testState = ConfigOptions.getTestState(getApplicationContext(), testCase.getTestName());

		if (testState.canRun()) {
			String titleText = "Running tests...";
			if (ConfigOptions.getExecutionMode(getApplicationContext()) == ConfigOptions.ExecutionMode.Interactive) {
				titleText = "Interactive test";
				this.interactiveTest = testCase;
				MenuItem item = menu.findItem(R.id.playTests);
				if (item != null) {
					item.setIcon(ResourcesCompat.getDrawable(getResources(), R.drawable.ic_done_action, null));
				}
				showOverflowMenu(true);
			}

			Objects.requireNonNull(getSupportActionBar()).setTitle(titleText);
			this.testResults.clear();
			if (ConfigOptions.getViewSetting(this) == ConfigOptions.ViewMapOption.ViewMap || ConfigOptions.getExecutionMode(getApplicationContext()) == ConfigOptions.ExecutionMode.Interactive) {
				selectFragment(this.viewTest);
			}
			this.executing = true;
		}
	}

	public void runTest(final MaplyTestCase testCase) {
		ConfigOptions.TestState testState = ConfigOptions.getTestState(getApplicationContext(), testCase.getTestName());

		if (testState.canRun()) {
			ConfigOptions.setTestState(getApplicationContext(), testCase.getTestName(), ConfigOptions.TestState.Executing);
			testCase.setOptions(ConfigOptions.getTestType(this));
			MaplyTestCase.MaplyTestCaseListener listener = new MaplyTestCase.MaplyTestCaseListener() {
				@Override
				public void onFinish(MaplyTestResult resultMap, MaplyTestResult resultGlobe) {
					if (resultMap != null) {
						MainActivity.this.testResults.add(resultMap);
					}
					if (resultGlobe != null) {
						MainActivity.this.testResults.add(resultGlobe);
					}
					finalizeTest(testCase);
				}

				@Override
				public void onStart(View view) {
					if (ConfigOptions.getViewSetting(MainActivity.this) == ConfigOptions.ViewMapOption.ViewMap || ConfigOptions.getExecutionMode(getApplicationContext()) == ConfigOptions.ExecutionMode.Interactive) {
						viewTest = new ViewTestFragment();
						viewTest.changeViewFragment(view);
						selectFragment(viewTest);
					}
				}

				@Override
				public void onExecute(View view) {
					if (ConfigOptions.getViewSetting(MainActivity.this) == ConfigOptions.ViewMapOption.ViewMap || ConfigOptions.getExecutionMode(getApplicationContext()) == ConfigOptions.ExecutionMode.Interactive) {
						viewTest = new ViewTestFragment();
						viewTest.changeViewFragment(view);
						selectFragment(viewTest);
					}
				}
			};
			testCase.setListener(listener);
			testCase.start();
		}
	}

	private void finalizeTest(MaplyTestCase testCase) {
		Objects.requireNonNull(getSupportActionBar()).setTitle(R.string.app_name);
		ConfigOptions.setTestState(getApplicationContext(), testCase.getTestName(), ConfigOptions.TestState.Ready);
		executing = false;
		Intent intent = new Intent(this, ResultActivity.class);
		Bundle bundle = new Bundle();
		bundle.putSerializable("arraylist", this.testResults);
		intent.putExtras(bundle);
		startActivity(intent);
	}

	private void finalizeInteractiveTest() {
		Objects.requireNonNull(getSupportActionBar()).setTitle(R.string.app_name);
		interactiveTest.cancel(true);
		interactiveTest.shutdown();
		ConfigOptions.setTestState(getApplicationContext(), interactiveTest.getTestName(), ConfigOptions.TestState.Ready);
		interactiveTest = null;
		MenuItem item = menu.findItem(R.id.playTests);
		if (item != null){
			item.setIcon(ResourcesCompat.getDrawable(getResources(), R.drawable.ic_play_action, null));
		}
		showOverflowMenu(false);
		executing = false;
		onResume();
	}

	public boolean isExecuting() {
		return executing;
	}

	@Override
	public void onItemClick(int itemId) {
		switch (itemId){
			case R.id.selectAll:
				testList.changeItemsState(true);
				drawerLayout.closeDrawer(GravityCompat.START);
				break;
			case R.id.deselectAll:
				testList.changeItemsState(false);
				drawerLayout.closeDrawer(GravityCompat.START);
				break;
			case R.id.runInteractive:
				showOverflowMenu(false);
				onResume();
				break;

			case R.id.runMultiple:
				showOverflowMenu(true);
				onResume();
				break;

			case R.id.runSingle:
				showOverflowMenu(false);
				onResume();
				break;
		}

		navigationDrawer.setSelectedItemId(itemId);
	}

	private void runTests() {
		MenuItem playButton = findViewById(R.id.playTests);
		playButton.setIcon(ResourcesCompat.getDrawable(getResources(), R.drawable.ic_stop_action, null));
		Objects.requireNonNull(getSupportActionBar()).setTitle("Running tests...");
		this.testResults.clear();
		MaplyTestCase[] tests = this.testList.getTests();
		if (ConfigOptions.getViewSetting(this) == ConfigOptions.ViewMapOption.ViewMap) {
			selectFragment(this.viewTest);
		}
		this.executing = true;
		startTests(tests, 0);
	}


	private void startTests(final MaplyTestCase[] tests, final int index) {
		if (tests.length != index) {
			final MaplyTestCase head = tests[index];
			if (ConfigOptions.getTestState(getApplicationContext(), head.getTestName()) == ConfigOptions.TestState.Selected) {
				head.setOptions(ConfigOptions.getTestType(this));
				ConfigOptions.setTestState(getApplicationContext(), head.getTestName(), ConfigOptions.TestState.Executing);
				MaplyTestCase.MaplyTestCaseListener listener = new MaplyTestCase.MaplyTestCaseListener() {
					@Override
					public void onFinish(MaplyTestResult resultMap, MaplyTestResult resultGlobe) {
						ConfigOptions.setTestState(getApplicationContext(), head.getTestName(), ConfigOptions.TestState.Selected);
						if (MainActivity.this.cancelled) {
							MainActivity.this.finishTests();
						} else {
							if (resultMap != null) {
								MainActivity.this.testResults.add(resultMap);
							}
							if (resultGlobe != null) {
								MainActivity.this.testResults.add(resultGlobe);
							}
							if (ConfigOptions.getViewSetting(MainActivity.this) == ConfigOptions.ViewMapOption.None) {
								head.setIcon(R.drawable.ic_action_selectall);
								MainActivity.this.testList.notifyIconChanged(index);
							}
							MainActivity.this.startTests(tests, index + 1);
						}
					}

					@Override
					public void onStart(View view) {

						if (ConfigOptions.getViewSetting(MainActivity.this) == ConfigOptions.ViewMapOption.ViewMap) {
							viewTest = new ViewTestFragment();
							viewTest.changeViewFragment(view);
							selectFragment(viewTest);
						}
					}

					@Override
					public void onExecute(View view) {
						if (ConfigOptions.getViewSetting(MainActivity.this) == ConfigOptions.ViewMapOption.ViewMap || ConfigOptions.getExecutionMode(getApplicationContext()) == ConfigOptions.ExecutionMode.Interactive) {
							viewTest = new ViewTestFragment();
							viewTest.changeViewFragment(view);
							selectFragment(viewTest);
						}
					}
				};
				head.setListener(listener);
				head.setActivity(this);
				if (ConfigOptions.getViewSetting(this) == ConfigOptions.ViewMapOption.None) {
					head.setIcon(R.drawable.ic_options_action);
					this.testList.notifyIconChanged(index);
				}
				head.start();
			} else {
				startTests(tests, index + 1);
			}
		} else {
			finishTests();
		}
	}

	private void finishTests() {
		MenuItem playButton = findViewById(R.id.playTests);
		playButton.setIcon(ResourcesCompat.getDrawable(getResources(), R.drawable.ic_play_action, null));
		Objects.requireNonNull(getSupportActionBar()).setTitle(R.string.app_name);
		executing = false;
		this.viewTest = new ViewTestFragment();
		if (!cancelled) {
			Intent intent = new Intent(this, ResultActivity.class);
			Bundle bundle = new Bundle();
			bundle.putSerializable("arraylist", this.testResults);
			intent.putExtras(bundle);
			startActivity(intent);
		} else {
			cancelled = false;
			this.testList = new TestListFragment();
			selectFragment(this.testList);
		}
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
	}

	private void stopTests() {
		Objects.requireNonNull(getSupportActionBar()).setTitle("Cancelling...");
		cancelled = true;
	}
}
