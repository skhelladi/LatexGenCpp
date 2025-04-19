#include "latexgen.h"
#include <iostream>
#include <memory>

using namespace LatexGen;

/**
 * Specific example showing the use of indexes in LaTeX documents with LatexGenC++
 */
int main()
{
    std::cout << "Creating an example of LaTeX index usage..." << std::endl;

    // Creating an article document with index
    Article article("Using Indexes in LatexGenCpp",
                    "Sofiane KHELLADI",
                    "April 19, 2025");

    // Enabling the index
    article.includeIndex(true);

    // Additional packages
    article.addPackage("listings");
    article.addPackage("xcolor");

    // Introduction section
    Section intro("Introduction", Section::Level::SECTION);
    intro.addContent("This document presents how to use indexing features with LatexGenCpp.");
    intro.addContent("Indexing is an important feature in technical and academic documents. "
                     "\\index{Indexing}");

    // Section on indexing features
    Section features("Indexing Features", Section::Level::SECTION);
    features.addContent("LatexGenCpp supports several types of indexing:");

    auto indexTypes = std::make_shared<List>(List::ListType::ITEMIZE);
    indexTypes->addItem("Simple index entries \\index{Simple entry}");
    indexTypes->addItem("Index entries with subentries \\index{Entry!Subentry}");
    indexTypes->addItem("Index entries with formatting \\index{Entry|textbf}");
    indexTypes->addItem("Index entries with cross-references \\index{Entry|see{Other entry}}");

    features.addContent(indexTypes->generate());

    // Section on practical use
    Section usage("Practical Usage", Section::Level::SECTION);
    usage.addContent("To use indexes in your documents, follow these steps:");

    auto indexSteps = std::make_shared<List>(List::ListType::ENUMERATE);
    indexSteps->addItem("Enable the index with the \\texttt{includeIndex(true)} method \\index{includeIndex}");
    indexSteps->addItem("Add index entries with the command \\texttt{\\textbackslash index\\{term\\}}");
    indexSteps->addItem("Compile the document with LaTeX to generate the .idx file");
    indexSteps->addItem("Run \\texttt{makeindex} on the .idx file to generate the .ind file");
    indexSteps->addItem("Compile the document again with LaTeX to incorporate the index");

    usage.addContent(indexSteps->generate());

    // Code example
    usage.addContent("Here is a code example to enable and use the index:");
    usage.addContent("\\begin{lstlisting}[language=C++]\n"
                     "// Enabling the index\n"
                     "document.includeIndex(true);\n\n"
                     "// Adding an index entry in the content\n"
                     "section.addContent(\"Text with index \\\\index{Term}\");\n"
                     "\\end{lstlisting}");

    // Section on types of index entries
    Section entryTypes("Types of Index Entries", Section::Level::SECTION);

    // Subsection for simple entries
    Section simpleEntry("Simple Entries", Section::Level::SUBSECTION);
    simpleEntry.addContent("A simple entry is created with \\texttt{\\textbackslash index\\{term\\}} \\index{Simple entry}");
    entryTypes.addContent(simpleEntry.generate());

    // Subsection for subentries
    Section subentry("Subentries", Section::Level::SUBSECTION);
    subentry.addContent("A subentry is created with \\texttt{\\textbackslash index\\{term!subterm\\}} \\index{Subentry!Example}");
    entryTypes.addContent(subentry.generate());

    // Subsection for formatting
    Section formatting("Entry Formatting", Section::Level::SUBSECTION);
    formatting.addContent("To format an entry, use \\texttt{\\textbackslash index\\{term|command\\}} \\index{Formatting|textbf}");
    formatting.addContent("Common commands are: \\texttt{textbf}, \\texttt{textit}, \\texttt{underline}");
    entryTypes.addContent(formatting.generate());

    // Subsection for cross-references
    Section crossRefs("Cross References", Section::Level::SUBSECTION);
    crossRefs.addContent("To create a cross-reference, use \\texttt{\\textbackslash index\\{term|see\\{other term\\}\\}} "
                         "\\index{Cross reference|see{See also}}");
    entryTypes.addContent(crossRefs.generate());

    // Conclusion section
    Section conclusion("Conclusion", Section::Level::SECTION);
    conclusion.addContent("Using indexes is a powerful feature to improve navigation in technical documents. "
                          "\\index{Navigation}");
    conclusion.addContent("LatexGenCpp facilitates the integration of indexes in your LaTeX documents. \\index{LatexGenCpp}");

    // Adding all sections to the document
    article.addSection(intro);
    article.addSection(features);
    article.addSection(usage);
    article.addSection(entryTypes);
    article.addSection(conclusion);

    // Saving the document to a file
    if (article.saveToFile("output", "example_index.tex"))
    {
        std::cout << "The file example_index.tex has been created successfully." << std::endl;
        std::cout << "To generate the index, run the following commands:" << std::endl;
        std::cout << "1. pdflatex example_index.tex" << std::endl;
        std::cout << "2. makeindex example_index.idx" << std::endl;
        std::cout << "3. pdflatex example_index.tex" << std::endl;
    }
    else
    {
        std::cerr << "Error creating the file example_index.tex" << std::endl;
    }

    return 0;
}