import qbs

Application {
    name: "qmetaenum"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }

    files: [
        "tst_qmetaenum.cpp",
    ]
}
