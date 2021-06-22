![WhirlyGlobe-Maply](/common/images/banner.jpg)

What is WhirlyGlobe-Maply?
---

WhirlyGlobe-Maply is a mapping toolkit with two parts, hence the dash. The WhirlyGlobe part is an interactive 3D globe. The Maply part is an interactive 2D map. There are separate view controllers (on iOS) for each, but otherwise they share 95% of their code.

This toolkit is used in [many apps](http://mousebird.github.io/WhirlyGlobe/apps/apps.html) from big, complicated apps to even more smaller, simpler apps. Feel free to use it in yours.

WhirlyGlobe-Maply is available for both iOS and Android.

Getting Started
---

If you're new to WhirlyGlobe-Maply, please [read the main page](http://mousebird.github.com/WhirlyGlobe/). See More Information below for useful links and resources.

There’s a tutorial for both iOS and Android:

- [Getting started with iOS](http://mousebird.github.io/WhirlyGlobe/tutorial/ios/getting_started.html) 
- [Getting started with Android](http://mousebird.github.io/WhirlyGlobe/tutorial/android/getting-started.html) 

Setup
---

Go to desired folder, then:

git clone https://github.com/calsurferpunk/WhirlyGlobe.git

cd WhirlyGlobe

git checkout develop

git submodule init

git submodule update

http://mousebird.github.io/WhirlyGlobe/tutorial/android/building-from-source.html

Cherry-pick a Commit
---

git fetch https://github.com/calsurferpunk/WhirlyGlobe develop

git cherry-pick

git push

Builds
---

[![iOS Build Status](https://app.bitrise.io/app/db108f10274df29b/status.svg?token=YvjbYKDqcvbKDzTqVxPRKA&branch=develop)](https://app.bitrise.io/app/db108f10274df29b) | iOS Develop
-: | :-
[![Android Build Status](https://app.bitrise.io/app/b262d073c2a02772/status.svg?token=ba6AKOKQvwu06rMJS5XyQg&branch=develop)](https://app.bitrise.io/app/b262d073c2a02772) | Android Develop

This is the develop branch of the WhirlyGlobe-Maply Component and API version 3.2. It should be easy to compile, as all the crazy dependencies are in submodules. You can also get a [precompiled version](https://mousebird-consulting-inc.github.io/WhirlyGlobe/builds/builds.html).

WhirlyGlobe-Maply uses a bunch of submodules, which you'll need to get. Like so:

```
git submodule init
git submodule update
```

Get comfortable. The data is contained in a submodule and it's large.

Once you get all this synced, try to build AutoTester. If it builds, you're good to go. Enjoy.

Want more detail? Go read the [Tutorials](http://mousebird.github.io/WhirlyGlobe/tutorial/) on the WhirlyGlobe-Maply site.

More Information
---

There's a [mailing list](http://eepurl.com/D30CD) for periodic announcements. Join!

Check out the [mousebird consulting blog](http://mousebirdconsulting.blogspot.com) for current progress.

Follow us on Twitter: [@whrlyglobemaply](https://twitter.com/whrlyglobemaply)

Email questions to: contact@mousebirdconsulting.com
