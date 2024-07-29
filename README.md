## About

This (header-only) library can be used to create an application using Qt, without the need of the
moc (MetaObject Compiler). It uses a different set of macro than Qt and templated constexpr code to
generate the QMetaObject at compile-time. It is entirely binary compatible with Qt.

Blog post presenting the project: https://woboq.com/blog/verdigris-qt-without-moc.html (2016)

Blog post with some implementation details: https://woboq.com/blog/verdigris-implementation-tricks.html (2018)

Github Actions:
[![Clang Tests](https://github.com/hicknhack-software/Qt-Verdigris/actions/workflows/clang.yml/badge.svg)](https://github.com/hicknhack-software/Qt-Verdigris/actions/workflows/clang.yml)
[![Gcc Tests](https://github.com/hicknhack-software/Qt-Verdigris/actions/workflows/gcc.yml/badge.svg)](https://github.com/hicknhack-software/Qt-Verdigris/actions/workflows/gcc.yml)
[![Windows Tests](https://github.com/hicknhack-software/Qt-Verdigris/actions/workflows/windows.yml/badge.svg)](https://github.com/hicknhack-software/Qt-Verdigris/actions/workflows/windows.yml)

## Documentation

For an introduction, see the [feature/main.cpp](https://github.com/hicknhack-software/Qt-Verdigris/blob/develop/tutorial/features/main.cpp).
See also a more detailed documetation of the macros in the source code.

For the advanced generic C++ API see the [app_api/main.cpp](https://github.com/hicknhack-software/Qt-Verdigris/blob/develop/tutorial/cpp_api/main.cpp)

For the experimantal QML_ELEMENT support, see [qml_element](https://github.com/hicknhack-software/Qt-Verdigris/tree/develop/tutorial/qml_element) folder.

## Status

Almost all features of Qt are working. The Qt test have been ported.

Features that are not yet working:
 - Q_PLUGIN_METADATA: This would require compiling to the Qt's binary json. Out of scope for now.
 - BINDABLE: Needs to be backported to the current C++ and Qt requirements.
 - QMetaMethod::tag(): Not yet implemented, could be supported if needed, but is not really needed
                       for anything. (not even tested by Qt's auto test)
 - Q_ENUM: Working, but requires to repeat the name of every enum value. Could be improved.

**New features compared to Qt with moc:**
 - Compile QObjects in single C++ compiler run.
 - Support for templated QObject.
 - Support for QObject nested in another class.
 
Some Quirks:
 - QML_ELEMENT: This is a Qt6 feature that automatically registers the QObjects for QML.
   Works by storing JSON in extra data segment that is dropped during linking.
   Only works on Posix, Mac or Windows targets.
   Requires CMake or Patched (Obj support) Qbs to work.


## How to Use

The library consist of only two headers files. You can either copy these header files in your
project, or adjust the include paths so that the compiler finds them.
You will find the headers in the 'src/' sub-directory.
Also make sure to set your compiler in, at least, C++20 mode. With qmake, you can do that with
`CONFIG += c++20`.

Tested with Qt >= 6.2.
Need a compiler that can do C++20 properly, such as GCC 12+ or Clang 13+, or MSVC 2019+.

### Translations

When running `lupdate`, add the argument `-tr-function-alias Q_DECLARE_TR_FUNCTIONS+=W_OBJECT` to
avoid the warning that your class are not using the Q_OBJECT macro.

### Correspondance Table

This table show the correspondence between Qt macro and Verdigris macro:

| Qt macro                                     | Use the Verdigris macro instead                   |
|----------------------------------------------|---------------------------------------------------|
| `Q_OBJECT`                                   | `W_OBJECT(MyClass)` ...  `W_OBJECT_IMPL(MyClass)` |
| `public slots: void mySlot(int x);`          |  `void mySlot(int x); W_SLOT(mySlot)`             |
| `signals: void mySignal(int x);`             |  `void mySignal(int x) W_SIGNAL(mySignal,x)`	     |
| `Q_PROPERTY(int myProperty WRITE setProp READ getProp NOTIFY propChanged)` | `W_PROPERTY(int, myProperty WRITE setProp READ getProp NOTIFY propChanged)` |
| `Q_GADGET`                                   | `W_GADGET(MyClass)` ...  `W_GADGET_IMPL(MyClass)` |
| `Q_INVOKABLE void myFunction(int foo);`      |  `void myFunction(int foo); W_INVOKABLE(myFunction)`
| `Q_INVOKABLE MyClass(int foo);`              |  `MyClass(int foo); W_CONSTRUCTOR(int)`           |
| `Q_CLASSINFO("foo", "bar")`                  | `W_CLASSINFO("foo", "bar")`                       |
| `Q_DECLARE_INTERFACE(MyInterface, "my.interface")` ... `Q_INTERFACE(MyInterface)`     | `Q_DECLARE_INTERFACE(MyInterface, "my.interface")` ... `W_INTERFACE(MyInterface)` |
| `Q_NAMESPACE`                                | `W_NAMESPACE(MyNs)` ...  `W_NAMESPACE_IMPL(MyNs)` |
| Q_ENUM/Q_FLAG/Q_ENUM_NS/Q_FLAG_NS            | W_ENUM/W_FLAG/W_ENUM_NS/W_FLAG_NS                 |

## Context

The macros were inspired by [CopperSpice](http://www.copperspice.com/).
The template code was based on previous work:
https://woboq.com/blog/reflection-in-cpp-and-qt-moc.html

Differences with CopperSpice:

1. Contrary to CopperSpice, this is not a fork of Qt, but just an alternative set of macro to define
   Qt objects and signals and slot in a way that is binary compatible with Qt, but does not require
   moc. This is to be used with the normal Qt. CopperSpice being an entire fork of Qt, it has more
   differences with Qt and is not kept up to date with all the new features coming in Qt.
2. The QMetaObject is built at compile time in the read only section (like what moc does).
   CopperSpice builds it at run-time when the library is loaded. So CopperSpice takes more memory
   and load slower.
3. With CopperSpice, you cannot declare your slot within the class definition.
4. CopperSpice uses `__LINE__` in its macro making it impossible to declare several things in one line
   or to declare objects or properties from macros.
5. The usability of some macro was (in our opinion) improved.
6. The additional Q_OBJECT_IMPL


## Licence

Like Qt, this library is under the dual licence LGPLv3 and GPLv2.
Being header-only, this removes many of the obligations of the LGPLv3.

If you have any questions or remark please email  info@woboq.com
