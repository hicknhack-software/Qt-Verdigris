import qbs
import qbs.Utilities

Project {
    references: [
        "signalbug"
    ]

    Application {
        name: "qobject"
        consoleApplication: true
        type: ["application", "autotest"]

        Depends { name: "cpp" }
        cpp.defines: base.concat("QT_DISABLE_DEPRECATED_BEFORE=0", "QT_NO_DEBUG")
        Depends { name: "Verdigris" }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.network" }
        Depends { name: "Qt.test" }
        Depends {
            name: "Qt.testlib-private"
            condition: Utilities.versionCompare(Qt.core.version, "6.2") >= 0
        }
        Depends { name: "signalbug" }

        Properties {
            condition: qbs.toolchain.contains('msvc')
            cpp.cxxFlags: base.concat(
                "/wd4573", // vs2019 warns about static connect/disconnect in lambdas
                "/wd4340" // vs2019 warns about wrapped enum value
            )
        }

        files: [
            "tst_qobject6.cpp",
        ]
    }

}
