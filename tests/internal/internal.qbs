import qbs

Application {
    name: "internal"
    consoleApplication: true

    Depends { name: "VerdigrisTest" }

    files: [
        "tst_internal.cpp"
    ]
}
