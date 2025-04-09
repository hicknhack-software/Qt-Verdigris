import qbs

Application {
    name: "qmetaproperty"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }

    files: [
        "tst_qmetaproperty6.cpp",
    ]
}
