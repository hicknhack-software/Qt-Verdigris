import qbs

Application {
    name: "qmetaobject"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }

    files: [
        "forwarddeclared.cpp",
        "forwarddeclared.h",
        "tst_qmetaobject6.cpp",
    ]
}
