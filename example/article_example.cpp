#include "latexgen.h"
#include <iostream>
#include <memory>

using namespace LatexGen;

/**
 * Example of generating a LaTeX article with LatexGenC++
 */
int main()
{
    std::cout << "Creating a LaTeX article example..." << std::endl;

    // Creating an article
    Article article("LaTeX Document Generation with LatexGenCpp",
                    "Sofiane KHELLADI",
                    "April 19, 2025",
                    Language::ENGLISH);

    // Adding packages
    article.addPackage("listings");
    article.addPackage("xcolor");
    article.addPackage("graphicx");

    // Configuring listings
    article.addInPreamble("\\lstset{\n"
                          "  basicstyle=\\small\\ttfamily,\n"
                          "  keywordstyle=\\color{blue}\\bfseries,\n"
                          "  commentstyle=\\color{green!60!black}\\itshape,\n"
                          "  stringstyle=\\color{purple},\n"
                          "  frame=single,\n"
                          "  breaklines=true,\n"
                          "  showstringspaces=false\n"
                          "}");

    // Adding an abstract
    article.setAbstract("This article presents LatexGenCpp, a C++ library "
                        "for programmatically generating LaTeX documents. "
                        "We demonstrate how to create a scientific article "
                        "with different sections, equations, and figures.");

    // Creating keywords
    article.addKeyword("LaTeX");
    article.addKeyword("C++");
    article.addKeyword("Document Generation");
    article.addKeyword("Scientific Writing");

    // Creating the first section
    Section intro("Introduction", Section::Level::SECTION);
    intro.addContent("LatexGenCpp is a C++ library that facilitates the creation of "
                     "LaTeX documents programmatically. This approach is particularly useful "
                     "when document content needs to be dynamically generated from "
                     "data or calculations.");

    intro.addContent("The library supports different types of LaTeX documents such as "
                     "articles, reports, books, and Beamer presentations.");

    // Adding a subsection
    Section motivation("Motivation", Section::Level::SUBSECTION);
    motivation.addContent("Programmatic generation of LaTeX documents offers several advantages:");

    // Creating a list using the new addList method
    auto advantages = article.addList(List::ListType::ITEMIZE);
    advantages->addItem("Automation of document creation");
    advantages->addItem("Consistency in structure and formatting");
    advantages->addItem("Ease of content updates");
    advantages->addItem("Integration with report generation systems");
    
    motivation.addContent("Programmatic generation of LaTeX documents offers several advantages:");
    motivation.addContent(advantages->generate());
    intro.addContent(motivation.generate());

    // Creating a second section
    Section usage("Using the Library", Section::Level::SECTION);
    usage.addContent("Using LatexGenCpp is simple and intuitive. Here is a "
                           "basic example of creating an article:");

    // Code example
    usage.addContent("\\begin{lstlisting}[language=C++]\n"
                           "#include \"latexgen.h\"\n"
                           "using namespace LatexGen;\n\n"
                           "int main() {\n"
                           "    // Creating an article\n"
                           "    Article article(\"Title\", \"Author\", \"Date\");\n\n"
                           "    // Adding a section\n"
                           "    Section section(\"Section Name\", Section::Level::SECTION);\n"
                           "    section.addContent(\"Section content\");\n\n"
                           "    // Adding the section to the article\n"
                           "    article.addSection(section);\n\n"
                           "    // Saving the document\n"
                           "    article.saveToFile(\"filename.tex\");\n"
                           "    return 0;\n"
                           "}\n"
                           "\\end{lstlisting}");

    // Subsection on features
    Section features("Advanced Features", Section::Level::SUBSECTION);
    features.addContent("The library also offers advanced features:");

    // Subsubsection on equations
    Section equations("Mathematical Equations", Section::Level::SUBSUBSECTION);
    equations.addContent("Equations can be easily integrated into the document using the addEquation method:");
    features.addContent(equations.generate());
    
    // Adding an equation with the new addEquation method
    auto equation = article.addEquation(
        "E = mc^2",               // Equation content
        "eq:einstein",            // Label for reference
        true                      // Numbered equation
    );
    
    // Adding an inline equation with the new addInlineEquation method
    std::string inlineEq = article.addInlineEquation("F = ma");
    
    article.addRawContent("Equation \\ref{eq:einstein} is Einstein's famous equation. " 
                          "Newton's second law can be written as " + inlineEq + ".");
    
    // Subsubsection on figures
    Section figures("Inserting Figures", Section::Level::SUBSUBSECTION);
    figures.addContent("Figures can be easily inserted using the addFigure method:");
    features.addContent(figures.generate());
    
    // Adding a figure with the new addFigure method
    auto architecture = article.addFigure(
        "architecture.png",                          // Image path
        "LatexGenCpp Architecture",                  // Caption
        "fig:architecture",                          // Label for reference
        "0.7\\textwidth",                            // Image width
        "htbp"                                       // Position
    );
    
    article.addRawContent("Figure \\ref{fig:architecture} shows the general architecture of the library.");

    // Subsubsection on tables
    Section tables("Tables", Section::Level::SUBSUBSECTION);
    tables.addContent("Here is an example of creating a table using the addTable method:");
    features.addContent(tables.generate());
    
    // Adding a table with the new addTable method
    std::vector<std::string> headers = {"Type", "Class", "Complexity"};
    auto types = article.addTable(
        headers,                               // Column headers
        "Supported Document Types",            // Caption
        "tab:types",                           // Label for reference
        "htbp"                                 // Position
    );
    
    // Adding rows to the table
    types->addRow({"Article", "Article", "Simple"});
    types->addRow({"Report", "Report", "Medium"});
    types->addRow({"Book", "Book", "High"});
    types->addRow({"Presentation", "Presentation", "Medium"});
    
    article.addRawContent("Table \\ref{tab:types} presents the different document types supported by the library.");

    // Creating a third section
    Section conclusion("Conclusion", Section::Level::SECTION);
    conclusion.addContent("LatexGenCpp offers an elegant solution for programmatically generating LaTeX "
                          "documents. Its object-oriented design and intuitive API make it a valuable tool "
                          "for projects requiring the generation of reports or scientific publications.");

    conclusion.addContent("Future developments will include support for more document types "
                          "and advanced features such as automatic generation of "
                          "bibliographies and glossaries.");

    // Adding sections to the document
    article.addSection(intro);
    article.addSection(usage);
    article.addSection(conclusion);

    // Configuring the bibliography using the new approach
    // Method 1: Using an existing external .bib file
    Bibliography biblio("references", BibStyle::IEEE);
    article.setBibliography(biblio);
    
    // Method 2 (alternative): Manually creating bibliography entries
    /*
    Bibliography biblio;
    biblio.setStyle(BibStyle::IEEE);
    
    // Creating an article entry
    BibEntry article_entry("smith2023", BibEntry::EntryType::ARTICLE);
    article_entry.addField("author", "John Smith");
    article_entry.addField("title", "Introduction to LaTeX Programming");
    article_entry.addField("journal", "Journal of Document Engineering");
    article_entry.addField("year", "2023");
    article_entry.addField("volume", "42");
    article_entry.addField("number", "1");
    article_entry.addField("pages", "123--456");
    
    // Adding the entry to the bibliography
    biblio.addEntry(article_entry);
    
    // Generating the .bib file
    biblio.generateBibFile("output");
    
    // Using the bibliography in the document
    article.setBibliography(biblio);
    */
    
    // Adding a citation
    article.addRawContent("According to " + article.cite("smith2023") + ", the theory is valid.");

    // Example of using theorems with the new addTheorem method
    auto theorem = article.addTheorem(
        TheoremEnvironment::Type::THEOREM,   // Theorem type
        "A + B = B + A",                     // Theorem content
        "Commutativity of Addition"          // Theorem title (optional)
    );

    // Example of using algorithms with the new addAlgorithm method
    auto algo = article.addAlgorithm(
        "Bubble Sort",          // Caption
        "algo:bubble"           // Label
    );
    
    // Configuring the algorithm
    algo->addFunction("BubbleSort", "A : array of integers");
    algo->addForLoop("i = 1 \\textbf{to} length(A)", 1);
    algo->addForLoop("j = 1 \\textbf{to} length(A) - i", 2);
    algo->addIf("A[j] > A[j+1]", 3);
    algo->addLine("swap A[j] and A[j+1]", 4);
    algo->addEnd("If", 3);
    algo->addEnd("For", 2);
    algo->addEnd("For", 1);
    algo->addReturn("A", 1);
    algo->addFunctionEnd(0);

    // Example of using custom templates
    DocumentTemplate academicTemplate("Academic");
    academicTemplate.setGeometry("margin=2.5cm");
    academicTemplate.setHeaderFooterStyle("fancy");
    academicTemplate.setHeader("", "\\thetitle", "\\thepage");
    academicTemplate.setFooter("\\theauthor", "", "\\today");
    academicTemplate.addPackage("microtype");
    academicTemplate.applyTo(article);

    // Saving the document
    if (article.saveToFile("output", "example_article.tex"))
    {
        std::cout << "The file example_article.tex has been created successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error creating the file example_article.tex" << std::endl;
    }

    return 0;
}