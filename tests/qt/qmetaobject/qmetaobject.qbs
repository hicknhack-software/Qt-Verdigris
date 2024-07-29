import qbs

Application {
    name: "qmetaobject"
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "Verdigris" }
    Depends { name: "Qt.test" }

    files: [
        "forwarddeclared.cpp",
        "forwarddeclared.h",
        "tst_qmetaobject6.cpp",
    ]
}
