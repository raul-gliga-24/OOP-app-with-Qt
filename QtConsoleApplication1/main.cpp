//#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include "Repository/Repository.h"
#include "Domain/Validator.h"
#include "Repository/FileRepo.h"
#include "Repository/ProbabilisticRepo.h"
#include "Service/Service.h"
#include "UI/UI.h"
#include "Tests/TestDomain.h"
#include "Tests/TestRepository.h"
#include "Tests/TestValidator.h"
#include "Tests/TestService.h"
#include "Tests/TestFileRepo.h"
#include "Tests/TestUndo.h"
#include "Tests/TestWorkList.h"

#include <qapplication.h>
#include "UI/GUI.h"

int main(int argc,char**argv) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    (void)_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    (void)_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    (void)_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    {
        std::cout << "Running tests: \n";
        run_tests_domain();
        run_tests_repository();
        run_validator_tests();
        run_service_tests();
        run_tests_file_repo();
        run_tests_undo();
        run_tests_worklist();
        std::cout << "Tests passed\n";
        std::cout << "\n";

        
        Repo* repo = new FileRepo("masini.csv");
        MasinaValidator val;
        Service srv(*repo, val);
        
        QApplication app(argc, argv);
        MainWindow window(srv);
        window.show();

        int result = app.exec();
        delete repo;
        return result;
    }
    _CrtDumpMemoryLeaks();
    return 0;
}