#include <iostream> // std::cerr
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE, std::exit
#include <ltiException.h> // lti::exception
#include "O3/except.h" // o3::nullpointer_exception, o3::precondition_violation, o3::postcondition_violation, o3::assertion_violation, o3::bad_index
#include "O3/final_act.h"
#include "RV_P01.h" // app::RvP01
#include "utils.h" // app::keepWindowOpen

//! main function; the entry point of the application
int main(int argc, char *argv[]) {
    // set up a safe cout flusher to flush cout in an exception safe manner
    o3::final_act<app::CoutFlusher> finalAct((app::CoutFlusher()));
    
    std::cout << "started running...\n";
    
    try {
        try {
            app::RvP01 instance; // instantiate app::RvP01
            instance(argc, argv); // call the call operator on instance, passing argc and argv.
        } catch (lti::exception const &e) {
            std::cerr << "caught lti::exception: " << e.what() << '\n';
            throw; // rethrow the exception
        } catch (o3::precondition_violation const &e) {
            std::cerr << "caught o3::precondition_violation: " << e.what() << '\n';
            throw; // rethrow the exception
        } catch (o3::postcondition_violation const &e) {
            std::cerr << "caught o3::postcondition_violation: " << e.what() << '\n';
            throw; // rethrow the exception
        } catch (o3::assertion_violation const &e) {
            std::cerr << "caught o3::assertion_violation: " << e.what() << '\n';
            throw; // rethrow the exception
        } catch (o3::nullpointer_exception const &e) {
            std::cerr << "caught o3::nullpointer_exception: " << e.what() << '\n';
            throw; // rethrow the exception
        } catch (o3::bad_index const &e) {
            std::cerr << "caught o3::bad_index: " << e.what() << '\n';
            throw; // rethrow the exception
        } catch (std::out_of_range const &e) {
            std::cerr << "caught std::out_of_range: " << e.what() << '\n';
            throw; // rethrow the exception
        } catch (std::logic_error const &e) {
            std::cerr << "caught std::logic_error: " << e.what() << '\n';
            throw; // rethrow the exception
        } catch (std::runtime_error const &e) {
            std::cerr << "caught std::runtime_error: " << e.what() << '\n';
            throw; // rethrow the exception
        } catch (std::exception const &e) {
            std::cerr << "caught std::exception: " << e.what() << '\n';
            throw; // rethrow the exception
        } catch (...) {
            std::cerr << "caught unkwown exception\n";
            throw; // rethrow the exception
        }
    } catch (...) { // catch the rethrown exception again
        // if we got in here an exception had been thrown -> exit with error
        app::keepWindowOpen("Exited with error, hit any key to exit");
        std::exit(EXIT_FAILURE); // exit the program indicating failure
    }

    return EXIT_SUCCESS; // exit the program indicating success
} // END of main
