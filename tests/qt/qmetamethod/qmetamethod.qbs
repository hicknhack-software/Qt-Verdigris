import qbs

Application {
    name: "qmetamethod"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }

    files: [
        "tst_qmetamethod6.cpp",
    ]
}
