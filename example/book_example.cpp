#include "latexgen.h"
#include <iostream>
#include <memory>

using namespace LatexGen;

/**
 * Example of generating a LaTeX book with LatexGenC++
 */
int main()
{
    std::cout << "Creating a LaTeX book example..." << std::endl;

    // Creating a book document
    Book book("Programming with LatexGenCpp",
               "Sofiane KHELLADI",
               "April 19, 2025",
               Language::ENGLISH);

    // Additional packages
    book.addPackage("listings");
    book.addPackage("xcolor");
    book.addPackage("graphicx");

    // Configuring listings
    book.addInPreamble("\\lstset{\n"
                        "  basicstyle=\\small\\ttfamily,\n"
                        "  keywordstyle=\\color{blue}\\bfseries,\n"
                        "  commentstyle=\\color{green!60!black}\\itshape,\n"
                        "  stringstyle=\\color{purple},\n"
                        "  frame=single,\n"
                        "  breaklines=true,\n"
                        "  showstringspaces=false\n"
                        "}");

    // Adding an abstract
    book.setAbstract("This book covers the LatexGenCpp library for programmatically generating LaTeX documents. "
                      "It includes comprehensive examples and explains the design principles behind the library.");

    // Activate table of contents and lists
    book.includeTableOfContents(true);
    book.includeListOfFigures(true);
    book.includeListOfTables(true);
    book.includeIndex(true); // Enable the index

    // Creating a custom part with chapters
    book.addPart("Introduction to LaTeX Document Generation");

    // Chapter 1: Introduction
    Section chapter1("Introduction to LatexGenCpp", Section::Level::CHAPTER);
    chapter1.addContent("LatexGenCpp is a C++ library designed for programmatic generation of LaTeX documents. "
                         "This chapter provides an overview of the library and its capabilities.");

    // Add a section to the chapter
    Section section1_1("The Need for Programmatic LaTeX Generation", Section::Level::SECTION);
    section1_1.addContent("Programmatic generation of LaTeX documents is useful in many scenarios, "
                          "especially when dealing with dynamic content or when integrating with data analysis systems.");
    section1_1.addContent("Some common use cases include:\\index{Use cases}");

    // Create a list for the use cases
    auto useCases = std::make_shared<List>(List::ListType::ITEMIZE);
    useCases->addItem("Generating scientific papers with dynamic data and charts");
    useCases->addItem("Creating customized reports for different clients");
    useCases->addItem("Producing academic materials with consistent formatting");
    useCases->addItem("Automating documentation for software projects");

    section1_1.addContent(useCases->generate());
    chapter1.addContent(section1_1.generate());

    // Add another section to the chapter
    Section section1_2("Key Features", Section::Level::SECTION);
    section1_2.addContent("LatexGenCpp offers a wide range of features:\\index{Features}");

    // Create a list for the features
    auto features = std::make_shared<List>(List::ListType::ITEMIZE);
    features->addItem("Support for different document types (articles, reports, books, presentations)\\index{Document types}");
    features->addItem("Object-oriented design for intuitive API");
    features->addItem("Handling of bibliographies, equations, figures, and tables");
    features->addItem("Multilingual support");

    section1_2.addContent(features->generate());
    chapter1.addContent(section1_2.generate());

    // Add the chapter to the first part
    book.addChapterToPart(chapter1);

    // Chapter 2: Getting Started
    Section chapter2("Getting Started", Section::Level::CHAPTER);
    chapter2.addContent("This chapter guides you through the installation and basic usage of LatexGenCpp. "
                         "We will also look at a simple example to get you started.");

    // Section for installation
    Section section2_1("Installation", Section::Level::SECTION);
    section2_1.addContent("To install LatexGenCpp, you need to follow these steps:\\index{Installation}");

    // Create a list for installation steps
    auto installationSteps = std::make_shared<List>(List::ListType::ENUMERATE);
    installationSteps->addItem("Clone the repository: \\texttt{git clone https://github.com/user/LatexGenCpp.git}");
    installationSteps->addItem("Navigate to the directory: \\texttt{cd LatexGenCpp}");
    installationSteps->addItem("Create a build directory: \\texttt{mkdir build \\&\\& cd build}");
    installationSteps->addItem("Run CMake: \\texttt{cmake ..}");
    installationSteps->addItem("Build the library: \\texttt{make}");
    installationSteps->addItem("Install the library: \\texttt{sudo make install}");

    section2_1.addContent(installationSteps->generate());

    // Section for basic usage
    Section section2_2("Basic Usage", Section::Level::SECTION);
    section2_2.addContent("Here is a simple example to create a basic article:\\index{Basic usage}");

    // Code example
    section2_2.addContent("\\begin{lstlisting}[language=C++]\n"
                           "#include \"latexgen.h\"\n"
                           "using namespace LatexGen;\n\n"
                           "int main() {\n"
                           "    // Create an article\n"
                           "    Article article(\"My First Document\", \"Author Name\", \"\\\\today\");\n\n"
                           "    // Add a section\n"
                           "    Section section(\"Introduction\", Section::Level::SECTION);\n"
                           "    section.addContent(\"This is the content of my first section.\");\n\n"
                           "    // Add the section to the article\n"
                           "    article.addSection(section);\n\n"
                           "    // Save the document\n"
                           "    article.saveToFile(\"output\", \"my_first_document.tex\");\n"
                           "    return 0;\n"
                           "}\n"
                           "\\end{lstlisting}");

    chapter2.addContent(section2_1.generate());
    chapter2.addContent(section2_2.generate());

    // Add the chapter to the first part
    book.addChapterToPart(chapter2);

    // Create a second part
    book.addPart("Advanced Features");

    // Chapter 3: Document Types
    Section chapter3("Document Types", Section::Level::CHAPTER);
    chapter3.addContent("LatexGenCpp supports several document types. This chapter explores "
                         "each document type and how to use them effectively.\\index{Document types}");

    // Sections for different document types
    Section section3_1("Articles", Section::Level::SECTION);
    section3_1.addContent("Articles are suitable for scientific papers, technical reports, and short documents. "
                           "\\index{Articles}");

    Section section3_2("Reports", Section::Level::SECTION);
    section3_2.addContent("Reports are designed for longer documents with chapters, such as technical reports "
                           "or business documents.\\index{Reports}");

    Section section3_3("Books", Section::Level::SECTION);
    section3_3.addContent("Books are for extensive documents with parts, chapters, and various front and back matter. "
                           "\\index{Books}");

    Section section3_4("Presentations", Section::Level::SECTION);
    section3_4.addContent("Presentations are for creating Beamer slides for talks and lectures. "
                           "\\index{Presentations}");

    chapter3.addContent(section3_1.generate());
    chapter3.addContent(section3_2.generate());
    chapter3.addContent(section3_3.generate());
    chapter3.addContent(section3_4.generate());

    // Add the chapter to the second part
    book.addChapterToPart(chapter3);

    // Chapter 4: Advanced Features
    Section chapter4("Advanced Features", Section::Level::CHAPTER);
    chapter4.addContent("This chapter covers advanced features of LatexGenCpp, including mathematical "
                         "equations, figures, tables, and more.");

    // Section for equations
    Section section4_1("Mathematical Equations", Section::Level::SECTION);
    section4_1.addContent("LatexGenCpp makes it easy to include mathematical equations in your documents. "
                           "\\index{Equations}");

    // Example of equation
    section4_1.addContent("Here is an example of creating a numbered equation:");
    section4_1.addContent("\\begin{lstlisting}[language=C++]\n"
                           "auto equation = document.addEquation(\n"
                           "    \"E = mc^2\",          // Equation content\n"
                           "    \"eq:einstein\",       // Label for reference\n"
                           "    true                   // Numbered equation\n"
                           ");\n"
                           "\\end{lstlisting}");

    // Section for figures
    Section section4_2("Figures", Section::Level::SECTION);
    section4_2.addContent("LatexGenCpp allows you to easily incorporate figures into your documents. "
                           "\\index{Figures}");

    // Example of figure
    section4_2.addContent("Here is an example of adding a figure:");
    section4_2.addContent("\\begin{lstlisting}[language=C++]\n"
                           "auto figure = document.addFigure(\n"
                           "    \"image.png\",                  // Image path\n"
                           "    \"Caption for the figure\",     // Caption\n"
                           "    \"fig:label\",                  // Label for reference\n"
                           "    \"0.8\\\\textwidth\",             // Width\n"
                           "    \"htbp\"                        // Position\n"
                           ");\n"
                           "\\end{lstlisting}");

    // Section for tables
    Section section4_3("Tables", Section::Level::SECTION);
    section4_3.addContent("Tables are an essential part of many documents, and LatexGenCpp provides "
                           "convenient methods to create and manipulate them. "
                           "\\index{Tables}");

    // Example of table
    section4_3.addContent("Here is an example of creating a table:");
    section4_3.addContent("\\begin{lstlisting}[language=C++]\n"
                           "std::vector<std::string> headers = {\"Column 1\", \"Column 2\", \"Column 3\"};\n"
                           "auto table = document.addTable(\n"
                           "    headers,                // Column headers\n"
                           "    \"Table Caption\",        // Caption\n"
                           "    \"tab:label\",            // Label for reference\n"
                           "    \"htbp\"                  // Position\n"
                           ");\n\n"
                           "// Adding rows\n"
                           "table->addRow({\"Value 1\", \"Value 2\", \"Value 3\"});\n"
                           "table->addRow({\"Value 4\", \"Value 5\", \"Value 6\"});\n"
                           "\\end{lstlisting}");

    chapter4.addContent(section4_1.generate());
    chapter4.addContent(section4_2.generate());
    chapter4.addContent(section4_3.generate());

    // Add the chapter to the second part
    book.addChapterToPart(chapter4);

    // Add an appendix
    Section appendix1("LaTeX Commands Reference", Section::Level::CHAPTER);
    appendix1.addContent("This appendix provides a quick reference to the most commonly used LaTeX commands.");

    auto commands = std::make_shared<List>(List::ListType::DESCRIPTION);
    commands->addItem("\\textbackslash documentclass", "Specifies the type of document");
    commands->addItem("\\textbackslash usepackage", "Imports a package");
    commands->addItem("\\textbackslash begin", "Starts an environment");
    commands->addItem("\\textbackslash end", "Ends an environment");
    commands->addItem("\\textbackslash section", "Creates a section");
    commands->addItem("\\textbackslash includegraphics", "Inserts an image");

    appendix1.addContent(commands->generate());
    book.addAppendix(appendix1);

    // Adding an example figure to demonstrate list of figures
    auto figure = book.addFigure(
        "architecture.png",              // Image path
        "LatexGenCpp Architecture",      // Caption
        "fig:architecture",              // Label for reference
        "0.7\\textwidth",                // Width
        "htbp"                           // Position
    );

    // Adding an example table to demonstrate list of tables
    std::vector<std::string> tableHeaders = {"Feature", "Supported", "Notes"};
    auto featureTable = book.addTable(
        tableHeaders,                          // Headers
        "LatexGenCpp Feature Support",         // Caption
        "tab:features",                        // Label
        "htbp"                                 // Position
    );

    // Add rows to the table
    featureTable->addRow({"Articles", "Yes", "Fully supported"});
    featureTable->addRow({"Reports", "Yes", "Fully supported"});
    featureTable->addRow({"Books", "Yes", "Fully supported"});
    featureTable->addRow({"Presentations", "Yes", "Fully supported"});
    featureTable->addRow({"Letters", "No", "Planned for future release"});

    // Saving the document
    if (book.saveToFile("output", "example_book.tex"))
    {
        std::cout << "The file example_book.tex has been created successfully." << std::endl;
        std::cout << "To generate the index, run the following commands:" << std::endl;
        std::cout << "1. pdflatex example_book.tex" << std::endl;
        std::cout << "2. makeindex example_book.idx" << std::endl;
        std::cout << "3. pdflatex example_book.tex" << std::endl;
    }
    else
    {
        std::cerr << "Error creating the file example_book.tex" << std::endl;
    }

    return 0;
}