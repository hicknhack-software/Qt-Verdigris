import qbs

Application {
    name: "templates"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }

    files: [
        "tst_templates.cpp",
    ]
}
