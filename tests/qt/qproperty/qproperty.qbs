import qbs

Application {
    name: "qproperty"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }
    Depends { name: "Qt.core-private" }

    files: [
        "tst_qproperty6.cpp",
    ]
}
