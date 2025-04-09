import qbs

Application {
    name: "basic"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }

    Group {
        name: "source"
        fileTags: ["unmocable"]
        overrideTags: false
        files: [
            "anothertu.cpp",
            "tst_basic.cpp",
            "anothertu.h",
        ]
    }
}
