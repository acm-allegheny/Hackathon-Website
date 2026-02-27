#include <emscripten.h>
#include <emscripten/bind.h>
#include <string>

// Tracks which page is currently active
std::string currentPage = "home";

void showPage(std::string id) {
    // Remove 'active' class from all pages
    emscripten_run_script(
        "document.querySelectorAll('.page')"
        ".forEach(p => p.classList.remove('active'));"
    );

    // Remove 'active' class from all nav links
    emscripten_run_script(
        "document.querySelectorAll('.nav-links a')"
        ".forEach(a => a.classList.remove('active'));"
    );

    // Add 'active' to the target page
    std::string showScript =
        "document.getElementById('" + id + "')"
        ".classList.add('active');";
    emscripten_run_script(showScript.c_str());

    // Highlight the correct nav link
    std::string navScript =
        "document.querySelector('.nav-links a[data-page=\"" + id + "\"]')"
        ".classList.add('active');";
    emscripten_run_script(navScript.c_str());

    // Scroll to top
    emscripten_run_script("window.scrollTo(0, 0);");

    // Update tracked page
    currentPage = id;
}

std::string getCurrentPage() {
    return currentPage;
}

// Expose functions so JavaScript/HTML can call them
EMSCRIPTEN_BINDINGS(hackathon) {
    emscripten::function("showPage", &showPage);
    emscripten::function("getCurrentPage", &getCurrentPage);
};
