import qbs

Application {
    name: "manyproperties"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }

    files: [
        "tst_manyproperties.cpp",
    ]
}
