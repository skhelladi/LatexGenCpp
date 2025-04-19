# LatexGenC++

A C++ library for programmatically generating LaTeX documents.

## Overview

LatexGenC++ is a comprehensive C++ library that allows programmatic generation of LaTeX documents. It provides an object-oriented API for creating various types of LaTeX documents, including articles, reports, books, and presentations, with support for multilingual content.

## Features

- **Multiple Document Types**: Support for articles, reports, books, and Beamer presentations
- **Structured Content**: Easy management of sections, subsections, chapters, parts, etc.
- **Rich Elements**: Figures, tables, equations, lists, theorems, algorithms
- **Bibliography Management**: Two methods for handling bibliographies:
  - Using external .bib files
  - Creating references programmatically
- **Multilingual Support**: 11 languages including English, French, German, Spanish, etc.
- **Custom Templates**: Apply consistent styling across documents
- **Index Generation**: Support for creating document indexes

## Installation

### Prerequisites

- C++ compiler with C++17 support
- CMake (version 3.10 or higher)

### Build and Install

```bash
# Clone the repository
git clone https://github.com/yourusername/LatexGenCpp.git

# Create a build directory
cd LatexGenCpp
mkdir build && cd build

# Configure and build
cmake ..
make

# Install (optional)
sudo make install
```

## Usage Examples

A detailed documentation is available in the `doc/` directory. Below are some basic usage examples to get you started. (hers is the link to the documentation: [FR](doc/DOCUMENTATION_FR.md), [EN](doc/DOCUMENTATION_EN.md))   

### Creating a Simple Article

```cpp
#include "latexgen.h"
#include <iostream>

using namespace LatexGen;

int main() {
    // Create an article
    Article article("My Document Title", "Author Name", "Today");
    
    // Add a section
    Section section("Introduction", Section::Level::SECTION);
    section.addContent("This is the content of my first section.");
    
    // Add the section to the article
    article.addSection(section);
    
    // Save the document
    if (article.saveToFile("output", "mydocument.tex")) {
        std::cout << "Document created successfully!" << std::endl;
    }
    
    return 0;
}
```

### Adding Figures and Tables

```cpp
// Adding a figure
auto figure = document.addFigure(
    "image.png",               // Image path
    "Figure Caption",          // Caption
    "fig:label",               // Label for reference
    "0.7\\textwidth",          // Width
    "htbp"                     // Position
);

// Adding a table
std::vector<std::string> headers = {"Column 1", "Column 2", "Column 3"};
auto table = document.addTable(
    headers,                   // Column headers
    "Table Caption",           // Caption
    "tab:label",               // Label for reference
    "htbp"                     // Position
);

// Adding rows to the table
table->addRow({"Value 1", "Value 2", "Value 3"});
table->addRow({"Value 4", "Value 5", "Value 6"});
```

### Using Bibliographies

```cpp
// Method 1: Using an existing external .bib file
Bibliography biblio("references", BibStyle::IEEE);
document.setBibliography(biblio);

// Method 2: Creating references programmatically
Bibliography biblio2;
biblio2.setStyle(BibStyle::IEEE);

// Create an article entry
BibEntry article("smith2023", BibEntry::EntryType::ARTICLE);
article.addField("author", "John Smith");
article.addField("title", "Introduction to LaTeX Programming");
article.addField("journal", "Journal of Document Engineering");
article.addField("year", "2023");
article.addField("volume", "42");
article.addField("pages", "123--456");

// Add the entry to the bibliography
biblio2.addEntry(article);

// Generate the .bib file
biblio2.generateBibFile("output");

// Use the bibliography in the document
document.setBibliography(biblio2);

// Cite a reference
document.addRawContent("According to " + document.cite("smith2023") + ", the theory is valid.");
```

## Documentation

For a comprehensive guide to all features, see the examples in the `example/` directory:

- `article_example.cpp`: Creating a scientific article
- `book_example.cpp`: Creating a book with parts, chapters, and appendices
- `report_example.cpp`: Creating a technical report
- `presentation_example.cpp`: Creating a Beamer presentation
- `index_example.cpp`: Using indexing features
- `multilingual_example.cpp`: Creating documents in different languages

## License

This project is licensed under the GPL-3.0 License. See the [LICENSE](LICENSE) file for details.

## Author

Sofiane KHELLADI

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.