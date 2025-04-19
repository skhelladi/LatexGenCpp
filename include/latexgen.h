#pragma once

/**
 * @file latexgen.h
 * @brief Header file for LaTeX generation functions.
 * @author Sofiane KHELLADI
 * @date 2025-04-18
 * @version 0.1.0
 * @note This library is designed to facilitate the creation of LaTeX documents.
 * @warning Ensure that all LaTeX commands are properly formatted.
 * @see https://www.latex-project.org/
 * @todo Implement additional LaTeX formatting functions.
 * @todo Add support for custom LaTeX templates.
 */

#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <memory>
#include <filesystem>
#include <set>

namespace LatexGen
{

    /**
     * @brief Enum for document class types
     */
    enum class DocumentType
    {
        ARTICLE,
        REPORT,
        BOOK,
        PRESENTATION
    };

    /**
     * @brief Enum for document languages
     */
    enum class Language
    {
        ENGLISH, // Default language
        FRENCH,
        GERMAN,
        SPANISH,
        ITALIAN,
        PORTUGUESE,
        DUTCH,
        RUSSIAN,
        CHINESE,
        JAPANESE,
        ARABIC
    };

    /**
     * @brief Enum for bibliography styles
     */
    enum class BibStyle
    {
        PLAIN,   // Basic style with numbered references
        ALPHA,   // Alpha-style with author-year labels
        ABBRV,   // Abbreviated style
        ACM,     // Association for Computing Machinery style
        IEEE,    // Institute of Electrical and Electronics Engineers style
        APA,     // American Psychological Association style
        CHICAGO, // Chicago style
        MLA,     // Modern Language Association style
        HARVARD, // Harvard style
        CUSTOM   // Custom style with user-defined .bst file
    };

    /**
     * @brief Function to get the babel language name from Language enum
     */
    std::string getBabelLanguageName(Language lang);

    /**
     * @brief Class to represent a LaTeX document section
     */
    class Section
    {
    public:
        enum class Level
        {
            CHAPTER = -1,     // For chapters (only for reports and books)
            SECTION = 0,      // For sections
            SUBSECTION = 1,   // For subsections
            SUBSUBSECTION = 2 // For subsubsections
        };

        Section(const std::string &title, Level level = Level::SECTION)
            : m_title(title), m_level(level) {}

        void addContent(const std::string &content)
        {
            m_content.push_back(content);
        }

        std::string generate() const;

    private:
        std::string m_title;
        Level m_level;
        std::vector<std::string> m_content;
    };

    /**
     * @brief Base class for LaTeX environment
     */
    class Environment
    {
    public:
        Environment(const std::string &name) : m_name(name) {}
        virtual ~Environment() = default;

        virtual std::string begin() const
        {
            return "\\begin{" + m_name + "}\n";
        }

        virtual std::string end() const
        {
            return "\\end{" + m_name + "}\n";
        }

        virtual std::string generate() const = 0;

    protected:
        std::string m_name;
    };

    /**
     * @brief Class for LaTeX tables
     */
    class Table : public Environment
    {
    public:
        Table(const std::vector<std::string> &headers, const std::string &position = "h")
            : Environment("table"), m_headers(headers)
        {
            m_options["position"] = position;
        }

        void setCaption(const std::string &caption)
        {
            m_caption = caption;
        }

        void setLabel(const std::string &label)
        {
            m_label = label;
        }

        void addRow(const std::vector<std::string> &row)
        {
            m_rows.push_back(row);
        }

        std::string generate() const override;

    private:
        std::vector<std::string> m_headers;
        std::vector<std::vector<std::string>> m_rows;
        std::string m_caption;
        std::string m_label;
        std::map<std::string, std::string> m_options;
    };

    /**
     * @brief Class for LaTeX figures
     */
    class Figure : public Environment
    {
    public:
        Figure(const std::string &imagePath, const std::string &position = "h")
            : Environment("figure"), m_imagePath(imagePath)
        {
            m_options["position"] = position;
        }

        void setCaption(const std::string &caption)
        {
            m_caption = caption;
        }

        void setLabel(const std::string &label)
        {
            m_label = label;
        }

        void setWidth(const std::string &width)
        {
            m_width = width;
        }

        std::string generate() const override;

    private:
        std::string m_imagePath;
        std::string m_caption;
        std::string m_label;
        std::string m_width = "0.8\\textwidth";
        std::map<std::string, std::string> m_options;
    };

    /**
     * @brief Class for LaTeX mathematical equations
     */
    class Equation : public Environment
    {
    public:
        Equation(bool numbered = true)
            : Environment(numbered ? "equation" : "equation*") {}

        void setContent(const std::string &content)
        {
            m_content = content;
        }

        void setLabel(const std::string &label)
        {
            m_label = label;
        }

        std::string generate() const override;

    private:
        std::string m_content;
        std::string m_label;
    };

    /**
     * @brief Class for LaTeX itemize and enumerate environments
     */
    class List : public Environment
    {
    public:
        enum class ListType
        {
            ITEMIZE,
            ENUMERATE,
            DESCRIPTION
        };

        List(ListType type = ListType::ITEMIZE)
            : Environment(type == ListType::ITEMIZE ? "itemize" : type == ListType::ENUMERATE ? "enumerate"
                                                                                              : "description"),
              m_type(type) {}

        void addItem(const std::string &item, const std::string &label = "")
        {
            m_items.push_back(item);
            if (!label.empty())
            {
                m_itemLabels[m_items.size() - 1] = label;
            }
        }

        std::string generate() const override;

    private:
        ListType m_type;
        std::vector<std::string> m_items;
        std::map<size_t, std::string> m_itemLabels; // For description lists
    };

    /**
     * @brief Reference entry for bibliography
     */
    class BibEntry
    {
    public:
        enum class EntryType
        {
            ARTICLE,
            BOOK,
            INPROCEEDINGS,
            TECHREPORT,
            PHDTHESIS,
            MASTERSTHESIS,
            MISC
        };

        BibEntry(const std::string &key, EntryType type)
            : m_key(key), m_type(type) {}

        void addField(const std::string &field, const std::string &value)
        {
            m_fields[field] = value;
        }

        std::string getKey() const
        {
            return m_key;
        }

        EntryType getType() const
        {
            return m_type;
        }

        const std::map<std::string, std::string> &getFields() const
        {
            return m_fields;
        }

        std::string generate() const;

        static std::string getTypeString(EntryType type);

    private:
        std::string m_key;
        EntryType m_type;
        std::map<std::string, std::string> m_fields;
    };

    /**
     * @brief Class to manage bibliographies in LaTeX documents
     */
    class Bibliography
    {
    public:
        /**
         * @brief Constructor for an external .bib file
         * @param bibFile Path to the .bib file (without extension)
         * @param style Bibliography style
         */
        Bibliography(const std::string &bibFile, BibStyle style = BibStyle::PLAIN)
            : m_bibFile(bibFile), m_style(style), m_customStyle(""), m_useExternalFile(true) {}

        /**
         * @brief Default constructor (empty bibliography)
         */
        Bibliography() 
            : m_bibFile("references"), m_style(BibStyle::PLAIN), m_customStyle(""), m_useExternalFile(false) {}

        /**
         * @brief Constructor for bibliography with custom style
         * @param bibFile Path to the .bib file (without extension)
         * @param customStyle Name of the custom .bst style file (without extension)
         */
        Bibliography(const std::string &bibFile, const std::string &customStyle)
            : m_bibFile(bibFile), m_style(BibStyle::CUSTOM), m_customStyle(customStyle), m_useExternalFile(true) {}

        /**
         * @brief Set the .bib file
         * @param bibFile Path to the .bib file (without extension)
         * @param useExternalFile If true, use an existing file. If false, generate the file.
         */
        void setBibFile(const std::string &bibFile, bool useExternalFile = true)
        {
            m_bibFile = bibFile;
            m_useExternalFile = useExternalFile;
        }

        /**
         * @brief Add a bibliography entry manually
         * @param entry Bibliography entry
         */
        void addEntry(const BibEntry &entry)
        {
            m_entries.push_back(entry);
            m_useExternalFile = false; // Use manual entries
        }

        /**
         * @brief Set the bibliography style
         * @param style Bibliography style
         */
        void setStyle(BibStyle style)
        {
            m_style = style;
            if (style != BibStyle::CUSTOM)
            {
                m_customStyle = "";
            }
        }

        /**
         * @brief Set a custom bibliography style
         * @param customStyle Name of the custom .bst style file (without extension)
         */
        void setCustomStyle(const std::string &customStyle)
        {
            m_style = BibStyle::CUSTOM;
            m_customStyle = customStyle;
        }

        /**
         * @brief Get the .bib file name
         * @return Path to the .bib file (without extension)
         */
        std::string getBibFile() const;

        /**
         * @brief Get configuration commands for the preamble
         * @return String containing LaTeX commands to configure the bibliography
         */
        std::string getPreambleConfig() const;

        /**
         * @brief Get commands to include the bibliography in the document
         * @param title Optional title for the bibliography section (if empty, the default language title is used)
         * @return String containing LaTeX commands to include the bibliography
         */
        std::string getIncludeCommands(const std::string &title = "") const;
        
        /**
         * @brief Generate the .bib file from manual entries
         * @param outputDir Output directory (optional)
         * @return true if the file was created successfully, false otherwise
         */
        bool generateBibFile(const std::string &outputDir = "") const;

    private:
        std::string m_bibFile;
        BibStyle m_style;
        std::string m_customStyle;
        bool m_useExternalFile;
        std::vector<BibEntry> m_entries;

        std::string getStyleName() const;
    };

    /**
     * @brief Class for mathematical theorem environments
     */
    class TheoremEnvironment : public Environment
    {
    public:
        /**
         * @brief Enum for theorem-like environment types
         */
        enum class Type
        {
            THEOREM,
            LEMMA,
            PROPOSITION,
            COROLLARY,
            DEFINITION,
            EXAMPLE,
            REMARK,
            PROOF,
            CUSTOM
        };

        /**
         * @brief Constructor for theorem environment
         * @param type Type of theorem environment
         * @param content Content of the theorem
         * @param title Optional title for the theorem
         */
        TheoremEnvironment(Type type, const std::string &content, const std::string &title = "")
            : Environment(getEnvironmentName(type)), m_type(type), m_content(content), m_title(title), m_customType("") {}

        /**
         * @brief Constructor for custom theorem environment
         * @param customType Name of the custom theorem environment
         * @param content Content of the theorem
         * @param title Optional title for the theorem
         */
        TheoremEnvironment(const std::string &customType, const std::string &content, const std::string &title = "")
            : Environment(customType), m_type(Type::CUSTOM), m_content(content), m_title(title), m_customType(customType) {}

        /**
         * @brief Set the content of the theorem
         * @param content Content of the theorem
         */
        void setContent(const std::string &content)
        {
            m_content = content;
        }

        /**
         * @brief Set the title of the theorem
         * @param title Title of the theorem
         */
        void setTitle(const std::string &title)
        {
            m_title = title;
        }

        /**
         * @brief Generate LaTeX code for the theorem environment
         * @return String containing LaTeX code
         */
        std::string generate() const override;

        /**
         * @brief Get the theorem environment setup for document preamble
         * @param language The document language for localization
         * @return String containing LaTeX commands for theorem environment setup
         */
        static std::string getTheoremSetup(Language language = Language::ENGLISH);

    private:
        Type m_type;
        std::string m_content;
        std::string m_title;
        std::string m_customType;

        static std::string getEnvironmentName(Type type);
    };

    /**
     * @brief Class for algorithm environments
     */
    class Algorithm : public Environment
    {
    public:
        /**
         * @brief Constructor for algorithm environment
         * @param caption Caption for the algorithm
         */
        Algorithm(const std::string &caption = "")
            : Environment("algorithm"), m_caption(caption) {}

        /**
         * @brief Set the caption of the algorithm
         * @param caption Caption of the algorithm
         */
        void setCaption(const std::string &caption)
        {
            m_caption = caption;
        }

        /**
         * @brief Set the label of the algorithm
         * @param label Label of the algorithm
         */
        void setLabel(const std::string &label)
        {
            m_label = label;
        }

        /**
         * @brief Add a line of pseudocode to the algorithm
         * @param line Line of pseudocode
         * @param indent Indentation level (0 = no indent)
         */
        void addLine(const std::string &line, int indent = 0)
        {
            m_lines.push_back({line, indent});
        }

        /**
         * @brief Add a comment line to the algorithm
         * @param comment Comment text
         * @param indent Indentation level (0 = no indent)
         */
        void addComment(const std::string &comment, int indent = 0)
        {
            m_lines.push_back({"\\" + std::string(indent > 0 ? ">\\" : "") + "Comment{" + comment + "}", indent});
        }

        /**
         * @brief Add a for loop to the algorithm
         * @param condition Loop condition
         * @param indent Indentation level (0 = no indent)
         */
        void addForLoop(const std::string &condition, int indent = 0)
        {
            m_lines.push_back({"\\For{" + condition + "}", indent});
            // m_lines.push_back({"\\Do", indent});
        }

        /**
         * @brief Add a while loop to the algorithm
         * @param condition Loop condition
         * @param indent Indentation level (0 = no indent)
         */
        void addWhileLoop(const std::string &condition, int indent = 0)
        {
            m_lines.push_back({"\\While{" + condition + "}", indent});
            // m_lines.push_back({"\\Do", indent});
        }

        /**
         * @brief Add an if statement to the algorithm
         * @param condition If condition
         * @param indent Indentation level (0 = no indent)
         */
        void addIf(const std::string &condition, int indent = 0)
        {
            m_lines.push_back({"\\If{" + condition + "}", indent});
            // m_lines.push_back({"\\Then", indent});
        }

        /**
         * @brief Add an else statement to the algorithm
         * @param indent Indentation level (0 = no indent)
         */
        void addElse(int indent = 0)
        {
            m_lines.push_back({"\\Else", indent});
        }

        /**
         * @brief Add an else if statement to the algorithm
         * @param condition Else if condition
         * @param indent Indentation level (0 = no indent)
         */
        void addElseIf(const std::string &condition, int indent = 0)
        {
            m_lines.push_back({"\\ElsIf{" + condition + "}", indent});
            // m_lines.push_back({"\\Then", indent});
        }

        /**
         * @brief Add an end statement to the algorithm (for closing loops, if statements, etc.)
         * @param statement Type of statement to end (e.g., "For", "If", "While")
         * @param indent Indentation level (0 = no indent)
         */
        void addEnd(const std::string &statement, int indent = 0)
        {
            m_lines.push_back({"\\End" + statement, indent});
        }

        /**
         * @brief Add a return statement to the algorithm
         * @param value Return value
         * @param indent Indentation level (0 = no indent)
         */
        void addReturn(const std::string &value, int indent = 0)
        {
            m_lines.push_back({"\n\\Return{" + value + "}", indent});
        }

        /**
         * @brief Add a break statement to the algorithm
         * @param indent Indentation level (0 = no indent)
         */
        void addBreak(int indent = 0)
        {
            m_lines.push_back({"\\Break", indent});
        }
        /**
         * @brief Add a continue statement to the algorithm
         * @param indent Indentation level (0 = no indent)
         */
        void addContinue(int indent = 0)
        {
            m_lines.push_back({"\\Continue", indent});
        }

        
        /**
         * @brief Add a function definition to the algorithm
         * @param name Function name
         * @param args Function arguments
         * @param indent Indentation level (0 = no indent)
         */
        void addFunction(const std::string &name, const std::string &args, int indent = 0)
        {
            m_lines.push_back({"\\Function{" + name + "}(" + args + ")", indent});
            // m_lines.push_back({"\\Do", indent});
        }
        /**
         * @brief Add a function end statement to the algorithm
         * @param indent Indentation level (0 = no indent)
         */
        void addFunctionEnd(int indent = 0)
        {
            m_lines.push_back({"\\EndFunction", indent});
        }
       
        /**
         * @brief Generate LaTeX code for the algorithm environment
         * @return String containing LaTeX code
         */
        std::string generate() const override;

        /**
         * @brief Get the algorithm package inclusion commands for document preamble
         * @return String containing LaTeX commands for algorithm package setup
         */
        static std::string getAlgorithmPackages();


    private:
        std::string m_caption;
        std::string m_label;
        std::vector<std::pair<std::string, int>> m_lines; // Line content, indentation level
    };

    /**
     * @brief Class to represent a document template
     */
    class DocumentTemplate
    {
    public:
        /**
         * @brief Constructor for document template
         * @param name Name of the template
         */
        DocumentTemplate(const std::string &name) : m_name(name) {}

        /**
         * @brief Add a package to the template
         * @param package Package name
         * @param options Package options
         */
        void addPackage(const std::string &package, const std::string &options = "")
        {
            m_packages[package] = options;
        }

        /**
         * @brief Add custom preamble content to the template
         * @param content Preamble content
         */
        void addPreambleContent(const std::string &content)
        {
            m_preambleContent.push_back(content);
        }

        /**
         * @brief Set page geometry
         * @param options Geometry options (e.g., "margin=1in")
         */
        void setGeometry(const std::string &options)
        {
            m_geometry = options;
        }

        /**
         * @brief Set header and footer style
         * @param style Header/footer style (e.g., "fancy")
         */
        void setHeaderFooterStyle(const std::string &style)
        {
            m_headerFooterStyle = style;
        }

        /**
         * @brief Set header content
         * @param left Left header content
         * @param center Center header content
         * @param right Right header content
         */
        void setHeader(const std::string &left, const std::string &center, const std::string &right)
        {
            m_headerLeft = left;
            m_headerCenter = center;
            m_headerRight = right;
        }

        /**
         * @brief Set footer content
         * @param left Left footer content
         * @param center Center footer content
         * @param right Right footer content
         */
        void setFooter(const std::string &left, const std::string &center, const std::string &right)
        {
            m_footerLeft = left;
            m_footerCenter = center;
            m_footerRight = right;
        }

        /**
         * @brief Apply template to a document
         * @param doc Document to apply template to
         */
        template <typename T>
        void applyTo(T &doc) const
        {
            // Add packages
            for (const auto &package : m_packages)
            {
                doc.addPackage(package.first, package.second);
            }

            // Add geometry if specified
            if (!m_geometry.empty())
            {
                doc.addPackage("geometry", m_geometry);
            }

            // Add header/footer if specified
            if (!m_headerFooterStyle.empty())
            {
                doc.addPackage("fancyhdr");
                std::stringstream headerFooterConfig;
                
                // Define \thetitle and \theauthor commands if they do not exist
                headerFooterConfig << "\\providecommand{\\thetitle}{" << doc.getTitle() << "}\n";
                headerFooterConfig << "\\providecommand{\\theauthor}{" << doc.getAuthor() << "}\n";
                headerFooterConfig << "\\pagestyle{" << m_headerFooterStyle << "}\n";

                if (!m_headerLeft.empty() || !m_headerCenter.empty() || !m_headerRight.empty())
                {
                    headerFooterConfig << "\\lhead{" << m_headerLeft << "}\n";
                    headerFooterConfig << "\\chead{" << m_headerCenter << "}\n";
                    headerFooterConfig << "\\rhead{" << m_headerRight << "}\n";
                }

                if (!m_footerLeft.empty() || !m_footerCenter.empty() || !m_footerRight.empty())
                {
                    headerFooterConfig << "\\lfoot{" << m_footerLeft << "}\n";
                    headerFooterConfig << "\\cfoot{" << m_footerCenter << "}\n";
                    headerFooterConfig << "\\rfoot{" << m_footerRight << "}\n";
                }

                doc.addInPreamble(headerFooterConfig.str());
            }

            // Add custom preamble content
            for (const auto &content : m_preambleContent)
            {
                doc.addInPreamble(content);
            }
        }

        /**
         * @brief Get the name of the template
         * @return Name of the template
         */
        std::string getName() const
        {
            return m_name;
        }

    private:
        std::string m_name;
        std::map<std::string, std::string> m_packages;
        std::vector<std::string> m_preambleContent;
        std::string m_geometry;
        std::string m_headerFooterStyle;
        std::string m_headerLeft;
        std::string m_headerCenter;
        std::string m_headerRight;
        std::string m_footerLeft;
        std::string m_footerCenter;
        std::string m_footerRight;
    };

    /**
     * @brief Base class for all LaTeX documents
     */
    class Document
    {
    public:
        Document(DocumentType type, const std::string &title = "",
                 const std::string &author = "", const std::string &date = "\\today",
                 Language language = Language::ENGLISH);
        virtual ~Document() = default;

        void setTitle(const std::string &title)
        {
            m_title = title;
        }

        void setAuthor(const std::string &author)
        {
            m_author = author;
        }

        void setDate(const std::string &date)
        {
            m_date = date;
        }

        void setLanguage(Language language)
        {
            m_language = language;
        }

        Language getLanguage() const
        {
            return m_language;
        }

        std::string getTitle() const
        {
            return m_title;
        }

        std::string getAuthor() const
        {
            return m_author;
        }

        void addPackage(const std::string &package, const std::string &options = "")
        {
            m_packages[package] = options;
        }

        void addSection(const Section &section)
        {
            m_sections.push_back(section);
        }

        void addEnvironment(std::shared_ptr<Environment> env)
        {
            m_environments.push_back(env);
        }

        void addRawContent(const std::string &content)
        {
            m_rawContent.push_back(content);
        }

        virtual std::string generatePreamble() const;
        virtual std::string generateDocument() const;
        virtual std::string generate() const;

        bool saveToFile(const std::string &Path, const std::string &filePath) const;

        /**
         * @brief Add a citation to the document
         * @param key Citation key from the bibliography
         * @return Citation command string
         */
        std::string cite(const std::string &key)
        {
            m_usedCitations.insert(key);
            return "\\cite{" + key + "}";
        }

        /**
         * @brief Add a citation with page numbers
         * @param key Citation key from the bibliography
         * @param pages Page numbers
         * @return Citation command string
         */
        std::string citePages(const std::string &key, const std::string &pages)
        {
            m_usedCitations.insert(key);
            return "\\cite[" + pages + "]{" + key + "}";
        }

        /**
         * @brief Add a bibliography to the document
         * @param bibliography Bibliography object
         */
        void setBibliography(const Bibliography &bibliography)
        {
            m_bibliography = bibliography;
        }

        /**
         * @brief Add theorem setup to the document preamble
         */
        void enableTheorems()
        {
            m_theoremsEnabled = true;
        }

        /**
         * @brief Add algorithm support to the document preamble
         */
        void enableAlgorithms()
        {
            m_algorithmsEnabled = true;
        }

        /**
         * @brief Add custom preamble content
         * @param content Preamble content
         */
        void addInPreamble(const std::string &content)
        {
            m_customPreamble.push_back(content);
        }

        /**
         * @brief Add a figure to the document
         * @param imagePath Path to the image file
         * @param caption Caption for the figure
         * @param label Label for references (optional)
         * @param width Width of the image (e.g., "0.8\\textwidth")
         * @param position Position specifier (e.g., "h", "ht", "htbp")
         * @return Pointer to the created Figure object
         */
        std::shared_ptr<Figure> addFigure(const std::string &imagePath, 
                                         const std::string &caption,
                                         const std::string &label = "",
                                         const std::string &width = "0.8\\textwidth",
                                         const std::string &position = "htbp");
        
        /**
         * @brief Add a table to the document
         * @param headers Vector of column headers
         * @param caption Caption for the table
         * @param label Label for references (optional)
         * @param position Position specifier (e.g., "h", "ht", "htbp")
         * @return Pointer to the created Table object
         */
        std::shared_ptr<Table> addTable(const std::vector<std::string> &headers,
                                       const std::string &caption,
                                       const std::string &label = "",
                                       const std::string &position = "htbp");

        /**
         * @brief Add a list to the document
         * @param type Type of list (itemize, enumerate, description)
         * @return Pointer to the created List object
         */
        std::shared_ptr<List> addList(List::ListType type = List::ListType::ITEMIZE);
        
        /**
         * @brief Add an equation to the document
         * @param content Equation content in LaTeX format
         * @param label Label for references (optional)
         * @param numbered Whether the equation should be numbered
         * @return Pointer to the created Equation object
         */
        std::shared_ptr<Equation> addEquation(const std::string &content,
                                             const std::string &label = "",
                                             bool numbered = true);
        
        /**
         * @brief Add an inline equation to the document
         * @param content Equation content in LaTeX format
         * @return Formatted string containing the inline equation
         */
        std::string addInlineEquation(const std::string &content);
        
        /**
         * @brief Add an algorithm to the document
         * @param caption Caption for the algorithm
         * @param label Label for references (optional)
         * @return Pointer to the created Algorithm object
         */
        std::shared_ptr<Algorithm> addAlgorithm(const std::string &caption,
                                               const std::string &label = "");
        
        /**
         * @brief Add a theorem environment to the document
         * @param type Type of theorem environment
         * @param content Content of the theorem
         * @param title Optional title for the theorem
         * @return Pointer to the created TheoremEnvironment object
         */
        std::shared_ptr<TheoremEnvironment> addTheorem(TheoremEnvironment::Type type,
                                                     const std::string &content,
                                                     const std::string &title = "");

    protected:
        DocumentType m_type;
        std::string m_title;
        std::string m_author;
        std::string m_date;
        Language m_language;
        std::map<std::string, std::string> m_packages;
        std::vector<Section> m_sections;
        std::vector<std::shared_ptr<Environment>> m_environments;
        std::vector<std::string> m_rawContent;
        std::vector<std::string> m_customPreamble;
        std::set<std::string> m_usedCitations;
        Bibliography m_bibliography;
        bool m_theoremsEnabled = false;
        bool m_algorithmsEnabled = false;

        std::string getDocumentClass() const;
        std::string getLanguageConfiguration() const;
    };

    /**
     * @brief Class for LaTeX article documents
     */
    class Article : public Document
    {
    public:
        Article(const std::string &title = "", const std::string &author = "",
                const std::string &date = "\\today", Language language = Language::ENGLISH)
            : Document(DocumentType::ARTICLE, title, author, date, language)
        {
            // Add default packages commonly used in articles
            addPackage("geometry", "margin=1in");
            addPackage("amsmath");
            addPackage("graphicx");
        }

        void setAbstract(const std::string &abstract)
        {
            m_abstract = abstract;
        }

        /**
         * @brief Add custom content to the document preamble
         * @param content Content to add to the preamble
         */
        void addInPreamble(const std::string &content)
        {
            m_customPreamble.push_back(content);
        }

        /**
         * @brief Add a keyword to the article
         * @param keyword Keyword to add
         */
        void addKeyword(const std::string &keyword)
        {
            m_keywords.push_back(keyword);
        }

        /**
         * @brief Enable or disable the index in the document
         * @param include If true, enable the index
         */
        void includeIndex(bool include = true)
        {
            m_includeIndex = include;
            if (include)
            {
                addPackage("imakeidx");
            }
        }

        std::string generatePreamble() const override;

        void createBibFile() const;

        void setBibliography(const Bibliography& bibliography);

        std::string generateDocument() const override;

    private:
        std::string m_abstract;
        std::vector<std::string> m_customPreamble; // To store custom preamble content
        std::vector<std::string> m_keywords;       // To store keywords
        bool m_includeIndex = false;               // To enable/disable the index
    };

    /**
     * @brief Class for LaTeX report documents
     */
    class Report : public Document
    {
    public:
        Report(const std::string &title = "", const std::string &author = "",
               const std::string &date = "\\today", Language language = Language::ENGLISH)
            : Document(DocumentType::REPORT, title, author, date, language)
        {
            // Add default packages commonly used in reports
            addPackage("geometry", "margin=1in");
            addPackage("amsmath");
            addPackage("graphicx");
            addPackage("hyperref");
            addPackage("tocloft");
        }

        void setAbstract(const std::string &abstract)
        {
            m_abstract = abstract;
        }

        void includeTableOfContents(bool include = true)
        {
            m_includeTableOfContents = include;
        }

        void includeListOfFigures(bool include = true)
        {
            m_includeListOfFigures = include;
        }

        void includeListOfTables(bool include = true)
        {
            m_includeListOfTables = include;
        }

        std::string generatePreamble() const override;
        std::string generateDocument() const override;

    private:
        std::string m_abstract;
        bool m_includeTableOfContents = false;
        bool m_includeListOfFigures = false;
        bool m_includeListOfTables = false;
    };

    /**
     * @brief Class for LaTeX book documents
     */
    class Book : public Document
    {
    public:
        Book(const std::string &title = "", const std::string &author = "",
             const std::string &date = "\\today", Language language = Language::ENGLISH)
            : Document(DocumentType::BOOK, title, author, date, language)
        {
            // Add default packages commonly used in books
            addPackage("geometry", "margin=1in");
            addPackage("amsmath");
            addPackage("graphicx");
            addPackage("hyperref");
            addPackage("tocloft");
            addPackage("bookmark");
        }

        void setAbstract(const std::string &abstract)
        {
            m_abstract = abstract;
        }

        void includeTableOfContents(bool include = true)
        {
            m_includeTableOfContents = include;
        }

        void includeListOfFigures(bool include = true)
        {
            m_includeListOfFigures = include;
        }

        void includeListOfTables(bool include = true)
        {
            m_includeListOfTables = include;
        }

        void includeIndex(bool include = true)
        {
            m_includeIndex = include;
            if (include)
            {
                addPackage("imakeidx");
            }
        }

        void addPart(const std::string &title)
        {
            m_parts.push_back(title);
            m_currentPart = m_parts.size() - 1;
        }

        void addChapterToPart(const Section &chapter)
        {
            if (m_currentPart >= 0 && m_currentPart < m_parts.size())
            {
                m_partChapters[m_currentPart].push_back(chapter);
            }
        }

        void addAppendix(const Section &appendix)
        {
            m_appendices.push_back(appendix);
        }

        std::string generatePreamble() const override;
        std::string generateDocument() const override;

    private:
        std::string m_abstract;
        bool m_includeTableOfContents = false;
        bool m_includeListOfFigures = false;
        bool m_includeListOfTables = false;
        bool m_includeIndex = false;
        std::vector<std::string> m_parts;
        std::map<size_t, std::vector<Section>> m_partChapters;
        std::vector<Section> m_appendices; // Add a vector to store appendices
        int m_currentPart = -1;
    };

    /**
     * @brief Class for LaTeX presentation documents (Beamer)
     */
    class Presentation : public Document
    {
    public:
        /**
         * @brief Theme for Beamer presentations
         */
        enum class Theme
        {
            DEFAULT,
            BERKELEY,
            MADRID,
            ANTIBES,
            COPENHAGEN,
            BERLIN,
            MANHATTAN,
            WARSAW,
            SINGAPORE
        };

        /**
         * @brief Color theme for Beamer presentations
         */
        enum class ColorTheme
        {
            DEFAULT,
            BEAVER,
            CRANE,
            DOLPHIN,
            DOVE,
            FLY,
            SEAGULL,
            WOLVERINE
        };

        /**
         * @brief Transition effect for slides
         */
        enum class Transition
        {
            NONE,
            FADE,
            PUSH,
            COVER,
            UNCOVER,
            SPLIT,
            BLINDS,
            WIPE
        };

        Presentation(const std::string &title = "", const std::string &author = "",
                     const std::string &date = "\\today", Language language = Language::ENGLISH,
                     Theme theme = Theme::DEFAULT, ColorTheme colorTheme = ColorTheme::DEFAULT)
            : Document(DocumentType::PRESENTATION, title, author, date, language),
              m_theme(theme), m_colorTheme(colorTheme)
        {
            // Add default packages commonly used in presentations
            addPackage("graphicx");
            addPackage("hyperref");
            addPackage("listings"); // Add listings package for code block support
            addPackage("xcolor");   // Add xcolor package for code coloring
        }

        void setInstitute(const std::string &institute)
        {
            m_institute = institute;
        }

        void setSubtitle(const std::string &subtitle)
        {
            m_subtitle = subtitle;
        }

        void setTheme(Theme theme)
        {
            m_theme = theme;
        }

        void setColorTheme(ColorTheme colorTheme)
        {
            m_colorTheme = colorTheme;
        }

        void setNavigation(bool show)
        {
            m_showNavigation = show;
        }

        void setTransition(Transition transition)
        {
            m_transition = transition;
        }

        void addSlide(const std::string &title, const std::string &content)
        {
            m_slides.push_back({title, {content}});
        }

        void addSlide(const std::string &title, const std::vector<std::string> &content)
        {
            m_slides.push_back({title, content});
        }

        /**
         * @brief Add a section to the presentation
         *
         * Add a section that will appear in the presentation structure and in the table of contents.
         * A section title slide will also be created if createFrame is true.
         *
         * @param title Title of the section
         * @param createFrame If true, create a slide with the section title
         */
        void addSection(const std::string &title, bool createFrame = true)
        {
            m_structure.push_back({Section::Level::SECTION, title, createFrame});
        }

        /**
         * @brief Add a subsection to the presentation
         *
         * Add a subsection that will appear in the presentation structure and in the table of contents.
         * A subsection title slide will also be created if createFrame is true.
         *
         * @param title Title of the subsection
         * @param createFrame If true, create a slide with the subsection title
         */
        void addSubsection(const std::string &title, bool createFrame = true)
        {
            m_structure.push_back({Section::Level::SUBSECTION, title, createFrame});
        }

        /**
         * @brief Add a subsubsection to the presentation
         *
         * @param title Title of the subsubsection
         * @param createFrame If true, create a slide with the subsubsection title
         */
        void addSubsubsection(const std::string &title, bool createFrame = false)
        {
            m_structure.push_back({Section::Level::SUBSUBSECTION, title, createFrame});
        }

        std::string generatePreamble() const override;
        std::string generateDocument() const override;

    private:
        std::string m_institute;
        std::string m_subtitle;
        Theme m_theme;
        ColorTheme m_colorTheme;
        Transition m_transition = Transition::NONE;
        bool m_showNavigation = true;
        std::vector<std::pair<std::string, std::vector<std::string>>> m_slides;
        std::vector<std::tuple<Section::Level, std::string, bool>> m_structure; // level, title, create a slide

        std::string getThemeName() const;
        std::string getColorThemeName() const;
        std::string getTransitionName() const;
        std::string getLevelCommand(Section::Level level) const;
    };

    

} // namespace LatexGen

using namespace LatexGen;
