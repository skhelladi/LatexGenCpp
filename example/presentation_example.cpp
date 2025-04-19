#include "latexgen.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace LatexGen;

/**
 * Example of generating a LaTeX Beamer presentation with LatexGenC++
 */
int main()
{
    std::cout << "Creating a LaTeX Beamer presentation example..." << std::endl;

    // Creating the presentation
    Presentation presentation("LatexGenCpp: A C++ Library for LaTeX Document Generation",
                              "Sofiane KHELLADI",
                              "April 19, 2025",
                              Language::ENGLISH,
                              Presentation::Theme::MADRID,
                              Presentation::ColorTheme::BEAVER);

    presentation.setSubtitle("A C++ library for creating LaTeX documents");
    presentation.setInstitute("University of Computer Science");
    presentation.setTransition(Presentation::Transition::FADE);

    // Adding the first section
    presentation.addSection("Introduction", true);

    // Introduction slides
    presentation.addSlide("Project Overview", "LatexGenCpp is a C++ library that allows "
                                              "programmatic generation of LaTeX documents.");

    presentation.addSlide("Objectives", "Library objectives:\n"
                                        "\\begin{itemize}\n"
                                        "\\item Facilitate the creation of LaTeX documents\n"
                                        "\\item Support different types of documents\n"
                                        "\\item Offer a simple and intuitive API\n"
                                        "\\item Handle multilingualism\n"
                                        "\\end{itemize}");

    // Adding a new section with subsections
    presentation.addSection("Document Types");

    // Subsection: Scientific Articles
    presentation.addSubsection("Scientific Articles");
    std::vector<std::string> articleContent;
    articleContent.push_back("The \\texttt{Article} class allows the creation of scientific articles:");
    articleContent.push_back("\\begin{itemize}");
    articleContent.push_back("\\item Support for sections and subsections");
    articleContent.push_back("\\item Management of abstracts");
    articleContent.push_back("\\item Academic formatting");
    articleContent.push_back("\\end{itemize}");
    presentation.addSlide("Features", articleContent);

    // Subsection: Technical Reports
    presentation.addSubsection("Technical Reports");
    presentation.addSlide("Report Structure",
                          "A technical report typically includes:\n"
                          "\\begin{itemize}\n"
                          "\\item A title page\n"
                          "\\item A table of contents\n"
                          "\\item Chapters and sections\n"
                          "\\item Appendices\n"
                          "\\end{itemize}");

    // Subsection: Books
    presentation.addSubsection("Books");

    // Slide with code - automatically adds the [fragile] option
    std::vector<std::string> bookExampleCode;
    bookExampleCode.push_back("Example of creating a book:");
    bookExampleCode.push_back("\\begin{lstlisting}[language=C++]");
    bookExampleCode.push_back("Book book(\"Book Title\", \"Author\");");
    bookExampleCode.push_back("book.addPart(\"First Part\");");
    bookExampleCode.push_back("Section chapter(\"Chapter 1\", Section::Level::CHAPTER);");
    bookExampleCode.push_back("book.addChapterToPart(chapter);");
    bookExampleCode.push_back("book.includeIndex(true);");
    bookExampleCode.push_back("\\end{lstlisting}");
    presentation.addSlide("Creating a Book", bookExampleCode);

    // Subsection: Presentations
    presentation.addSubsection("Presentations");
    presentation.addSlide("Beamer Features",
                          "Beamer presentations support:\n"
                          "\\begin{itemize}\n"
                          "\\item Different visual themes\n"
                          "\\item Transitions between slides\n"
                          "\\item Hierarchical organization (sections)\n"
                          "\\item Progressive content display\n"
                          "\\end{itemize}");

    // New section on multilingual support
    presentation.addSection("Multilingual Support");

    // Slide with image
    std::vector<std::string> slideFigure;
    slideFigure.push_back("LatexGenCpp supports 11 different languages:");
    slideFigure.push_back("\\begin{figure}");
    slideFigure.push_back("\\centering");
    slideFigure.push_back("\\includegraphics[width=0.7\\textwidth]{architecture.png}");
    slideFigure.push_back("\\caption{Multilingual architecture of LatexGenCpp}");
    slideFigure.push_back("\\end{figure}");
    presentation.addSlide("Supported Languages", slideFigure);

    // Sub-subsection (without automatic title frame)
    presentation.addSubsubsection("Specific Configuration", false);
    presentation.addSlide("Language Configuration",
                          "Each language requires specific configuration:\n"
                          "\\begin{itemize}\n"
                          "\\item Babel or polyglossia packages\n"
                          "\\item Support for special characters\n"
                          "\\item Adapted typographic rules\n"
                          "\\end{itemize}");

    // Section on advanced features with a sub-subsection
    presentation.addSection("Advanced Features");
    presentation.addSubsection("Mathematical Equations");

    // Slide with equation
    std::vector<std::string> slideEquation;
    slideEquation.push_back("The following equation represents the relationship between LaTeX and productivity:");
    slideEquation.push_back("\\begin{equation*}");
    slideEquation.push_back("Productivity = \\frac{Quality \\times Documents}{Time}");
    slideEquation.push_back("\\end{equation*}");
    presentation.addSlide("Magic Formula", slideEquation);

    // Final slide
    presentation.addSection("Conclusion");
    presentation.addSlide("Summary", "LatexGenCpp offers an elegant solution for "
                                     "programmatically generating high-quality LaTeX documents "
                                     "in different languages and formats.");

    // Saving the presentation document
    if (presentation.saveToFile("output", "example_presentation.tex"))
    {
        std::cout << "The file example_presentation.tex has been created successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error creating the file example_presentation.tex" << std::endl;
    }

    return 0;
}