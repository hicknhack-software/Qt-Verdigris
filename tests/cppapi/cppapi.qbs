import qbs

Application {
    name: "cppapi"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }

    files: [
        "tst_cppapi.cpp",
    ]
}
