#include <iostream> // std::cerr
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE, std::exit
#include <ltiException.h> // lti::exception
#include "O3/except.h" // o3::nullpointer_exception, o3::precondition_violation, o3::postcondition_violation, o3::assertion_violation, o3::bad_index
#include "RV_P01.h" // app::RvP01
#include "utils.h"

int main(int argc, char *argv[]) {
    try {
        try {
            app::RvP01 instance;
            instance(argc, argv);
        } catch (lti::exception const &e) {
            std::cerr << "caught lti::exception: " << e.what() << '\n';
            throw;
        } catch (o3::precondition_violation const &e) {
            std::cerr << "caught o3::precondition_violation: " << e.what() << '\n';
            throw;
        } catch (o3::postcondition_violation const &e) {
            std::cerr << "caught o3::postcondition_violation: " << e.what() << '\n';
            throw;
        } catch (o3::assertion_violation const &e) {
            std::cerr << "caught o3::assertion_violation: " << e.what() << '\n';
            throw;
        } catch (o3::nullpointer_exception const &e) {
            std::cerr << "caught o3::nullpointer_exception: " << e.what() << '\n';
            throw;
        } catch (o3::bad_index const &e) {
            std::cerr << "caught o3::bad_index: " << e.what() << '\n';
            throw;
        } catch (std::out_of_range const &e) {
            std::cerr << "caught std::out_of_range: " << e.what() << '\n';
            throw;
        } catch (std::logic_error const &e) {
            std::cerr << "caught std::logic_error: " << e.what() << '\n';
            throw;
        } catch (std::runtime_error const &e) {
            std::cerr << "caught std::runtime_error: " << e.what() << '\n';
            throw;
        } catch (std::exception const &e) {
            std::cerr << "caught std::exception: " << e.what() << '\n';
            throw;
        } catch (...) {
            std::cerr << "caught unkwown exception\n";
            throw;
        }
    } catch (...) {
        app::keepWindowOpen("Exited with error, hit any key to exit");
        std::exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
} // END of main