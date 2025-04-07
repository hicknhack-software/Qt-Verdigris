import qbs

Application {
    id: root
    name: "signalbug"
    type: ["application", "autotest-required"]
    consoleApplication: true

    Depends { name: "Verdigris" }

    files: [
        "signalbug.cpp",
        "signalbug.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.defines: base.concat("W_SIGNALBUG=\""+root.buildDirectory+"/"+root.targetName+"\"")
    }
}
