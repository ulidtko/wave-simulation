wave-simulation
===============

*An C++11/CMake/Boost/Qt/OpenGL excersize.*

This code started in Feb 2012 as an employment excersize. Local Samsung R&D center[¹] gave me an assignment, which was roughly formulated as "Make a wave going over a picture. Bonus points for reflections, radial waves, etc."

[¹]: http://www.samsung.com/ua/aboutsamsung/careers/samsungukraineresearchcenter/SamsungUkraineResearchCenter.html

I approached the problem by continuously solving the two-dimensional [wave equation] for a 2D displacement vector field using the [finite difference method]. Then there was a visualization using [QGLWidget].

[wave equation]: https://en.wikipedia.org/wiki/Wave_equation
[finite difference method]: http://en.wikipedia.org/wiki/Finite_difference_method
[QGLWidget]: http://qt-project.org/doc/qt-4.8/qglwidget.html

The primary use of the code was **to be read**, by my interviewers. Thus I had a lovely excuse to making the whole project's code pretty and enjoyable to read. Yet it still even works!

The points I'm especially proud of in the codebase:
 
 * The use of a descriptive build system, [CMake]. Just start reading from the top-level [CMakeLists.txt][blob/master/CMakeLists.txt], then compare that with what you'd be seeing with MSVC, or say, XCode project files. Hint: massive repetitive barely readable, uneditable, un-vcs-mergeable hunks of GUID-filled piles of XML — none of that with CMake. That's why I love it (and also for nice&clear colorful `make` output with build percentage gauge; and for the `ccmake` build configuration tool; also for cross-platform generator backends (which means CMake generates GNU Makefiles, MSVC .vcproj files, XCode .xcodeproj's, etc — so that you can build the same CMake project on different platforms with different compilers and toolchains), easy IDE integration and modularity. Wait, did I just forget to mention its (by itself awesome) backwards compatibility [manamement system][cmake policies]?). Yeah... I love CMake.
 
[CMake]: http://www.cmake.org/
[CMake policies]: http://www.cmake.org/Wiki/CMake/Policies

 * The use of C++11. Back in February 2012 it was still new and cool and exciting. You'll find quite some C++11 features used directly in the code; as this was my personal project, I dropped them in whenever I could, just to try it out. Great stuff.
 
 * The separation of GUI-unrelated simulation logic from GUI itself. The core code is actually compiled as an independent static library (again, enjoy the breeze of CMake handling it), which doesn't link to Qt. Even for this small-sized project proper decoupling and separation of concerns is important: coding ODE solving inside the `onTimer` Qt event handler would be really bad engineering. In fact, I wanted to build an Android GUI too, very possibly with some touch input — and for this to ever happen (Qt 5 wasn't yet released back then), it'd be necessary for the core simulation library to be strictly separated from Qt GUI. And then some NDK with JNI, but that's an easy part.
 
 * The use of external components. As much as I liked braking up the monolithic project to loosely coupled components, I liked plugging in open-source components which I didn't write. I used Qt for GUI, OpenGL for drawing (like, 4 or 5 gl calls total in the code — but still, it's used), [Eigen] with [UmfPack] plugin for solving sparse algebra. I also like how all the dependencies are clearly declared in the top-level [`CMakeLists.txt`][blob/master/CMakeLists.txt]. It's... beautiful.
 
[Eigen]: http://eigen.tuxfamily.org
[UmfPack]: http://www.cise.ufl.edu/research/sparse/umfpack/

For any questions drop me a letter. I hope you enjoy reading the code as much as I enjoyed writing it.
