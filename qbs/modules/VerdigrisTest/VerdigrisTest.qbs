Module {
    additionalProductTypes: ["autotest"]

    Depends { name: "Verdigris" }
    Depends { name: "Qt.test" }

    Depends { name: "autotest" }
    autotest.arguments: ['-o', (project.junit_output ? project.sourceDirectory + "/reports/" + product.name + ".xml,junitxml" : "-")]
}
