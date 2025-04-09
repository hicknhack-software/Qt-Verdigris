import qbs

Application {
    name: "inherit"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }

    files: [
        "api1.h",
        "api2.h",
        "object.cpp",
        "object.h",
        "tst_inherit.cpp",
    ]
}
