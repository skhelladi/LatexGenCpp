#include "latexgen.h"

namespace LatexGen
{

    /**
     * Utility function to process math equations in presentations
     * This function replaces accented characters in math environments
     */
    std::string sanitizeMathContent(const std::string &content)
    {
        std::string result = content;

        // Search for math environments and replace accents
        // Environments to watch: equation, equation*, align, align*, etc.
        std::vector<std::string> mathEnvs = {
            "\\begin{equation}", "\\end{equation}",
            "\\begin{equation*}", "\\end{equation*}",
            "\\begin{align}", "\\end{align}",
            "\\begin{align*}", "\\end{align*}",
            "$", "$$"};

        bool inMathMode = false;
        std::string::size_type pos = 0;
        std::string::size_type startMathPos = 0;

        while (pos < result.length())
        {
            bool foundEnv = false;

            for (const auto &env : mathEnvs)
            {
                if (result.compare(pos, env.length(), env) == 0)
                {
                    // If a math environment marker is found
                    foundEnv = true;

                    if (!inMathMode)
                    {
                        // Start of a math environment
                        inMathMode = true;
                        startMathPos = pos + env.length();
                    }
                    else
                    {
                        // End of a math environment
                        inMathMode = false;

                        // Process the content between startMathPos and pos
                        std::string mathContent = result.substr(startMathPos, pos - startMathPos);

                        // Replace accented characters with their TeX equivalents in math mode
                        // Note: in math mode, accents must be on letters in text mode
                        std::map<std::string, std::string> replacements = {
                            {"é", "\\text{é}"},
                            {"è", "\\text{è}"},
                            {"ê", "\\text{ê}"},
                            {"à", "\\text{à}"},
                            {"ù", "\\text{ù}"},
                            {"ç", "\\text{ç}"},
                            {"Productivité", "\\text{Productivité}"},
                            {"Qualité", "\\text{Qualité}"},
                            {"Documents", "\\text{Documents}"},
                            {"Temps", "\\text{Temps}"}};

                        for (const auto &rep : replacements)
                        {
                            std::string::size_type repPos = 0;
                            while ((repPos = mathContent.find(rep.first, repPos)) != std::string::npos)
                            {
                                mathContent.replace(repPos, rep.first.length(), rep.second);
                                repPos += rep.second.length();
                            }
                        }

                        // Replace the original content with the processed content
                        result.replace(startMathPos, pos - startMathPos, mathContent);

                        // Adjust the position after replacement
                        pos = startMathPos + mathContent.length() + env.length();
                        break;
                    }

                    pos += env.length();
                    break;
                }
            }

            if (!foundEnv)
            {
                pos++;
            }
        }

        return result;
    }

    /**
     * Implementation for the getBabelLanguageName function
     */
    std::string getBabelLanguageName(Language lang)
    {
        switch (lang)
        {
        case Language::ENGLISH:
            return "english";
        case Language::FRENCH:
            return "french";
        case Language::GERMAN:
            return "german,provide=*"; // Use provide=* as suggested in the error
        case Language::SPANISH:
            return "spanish,provide=*"; // Use provide=* as suggested in the error
        case Language::ITALIAN:
            return "italian,provide=*"; // Use provide=* as suggested in the error
        case Language::PORTUGUESE:
            return "portuguese,provide=*";
        case Language::DUTCH:
            return "dutch,provide=*";
        case Language::RUSSIAN:
            return "russian,provide=*";
        case Language::CHINESE:
            return "chinese,provide=*";
        case Language::JAPANESE:
            return "japanese,provide=*";
        case Language::ARABIC:
            return "arabic,provide=*";
        default:
            return "english";
        }
    }

    /**
     * Implementation for Section class
     */
    std::string Section::generate() const
    {
        std::string result;

        // Generate the section command based on level
        switch (m_level)
        {
        case Level::CHAPTER:
            result = "\\chapter{" + m_title + "}\n";
            break;
        case Level::SECTION:
            result = "\\section{" + m_title + "}\n";
            break;
        case Level::SUBSECTION:
            result = "\\subsection{" + m_title + "}\n";
            break;
        case Level::SUBSUBSECTION:
            result = "\\subsubsection{" + m_title + "}\n";
            break;
        default:
            result = "\\paragraph{" + m_title + "}\n";
        }

        // Add content
        for (const auto &content : m_content)
        {
            result += content + "\n";
        }

        return result;
    }

    /**
     * Implementation for Table class
     */
    std::string Table::generate() const
    {
        std::stringstream ss;

        // Begin table environment with position
        ss << "\\begin{table}";
        if (!m_options.empty() && m_options.find("position") != m_options.end())
        {
            ss << "[" << m_options.at("position") << "]";
        }
        ss << "\n\\centering\n";

        // Calculate number of columns and set tabular environment
        size_t numCols = m_headers.size();
        ss << "\\begin{tabular}{";
        for (size_t i = 0; i < numCols; ++i)
        {
            ss << "|c";
        }
        ss << "|}\n\\hline\n";

        // Add headers
        for (size_t i = 0; i < numCols; ++i)
        {
            ss << m_headers[i];
            if (i < numCols - 1)
            {
                ss << " & ";
            }
        }
        ss << " \\\\ \\hline\n";

        // Add rows
        for (const auto &row : m_rows)
        {
            for (size_t i = 0; i < row.size() && i < numCols; ++i)
            {
                ss << row[i];
                if (i < numCols - 1)
                {
                    ss << " & ";
                }
            }
            ss << " \\\\ \\hline\n";
        }

        // End tabular environment
        ss << "\\end{tabular}\n";

        // Add caption and label if provided
        if (!m_caption.empty())
        {
            ss << "\\caption{" << m_caption << "}\n";
        }

        if (!m_label.empty())
        {
            ss << "\\label{" << m_label << "}\n";
        }

        // End table environment
        ss << "\\end{table}\n";

        return ss.str();
    }

    /**
     * Implementation for Figure class
     */
    std::string Figure::generate() const
    {
        std::stringstream ss;

        // Begin figure environment with position
        ss << "\\begin{figure}";
        if (!m_options.empty() && m_options.find("position") != m_options.end())
        {
            ss << "[" << m_options.at("position") << "]";
        }
        ss << "\n\\centering\n";

        // Include the image
        ss << "\\includegraphics";
        if (!m_width.empty())
        {
            ss << "[width=" << m_width << "]";
        }
        ss << "{" << m_imagePath << "}\n";

        // Add caption and label if provided
        if (!m_caption.empty())
        {
            ss << "\\caption{" << m_caption << "}\n";
        }

        if (!m_label.empty())
        {
            ss << "\\label{" << m_label << "}\n";
        }

        // End figure environment
        ss << "\\end{figure}\n";

        return ss.str();
    }

    /**
     * Implementation for Equation class
     */
    std::string Equation::generate() const
    {
        std::stringstream ss;

        // Begin equation environment
        ss << begin();

        // Add the equation content
        ss << m_content << "\n";

        // Add label if provided
        if (!m_label.empty())
        {
            ss << "\\label{" << m_label << "}\n";
        }

        // End equation environment
        ss << end();

        return ss.str();
    }

    /**
     * Implementation for List class
     */
    std::string List::generate() const
    {
        std::stringstream ss;

        // Begin list environment
        ss << begin();

        // Add items
        for (size_t i = 0; i < m_items.size(); ++i)
        {
            ss << "\\item ";

            // For description lists, add an optional label
            if (m_type == ListType::DESCRIPTION && m_itemLabels.find(i) != m_itemLabels.end())
            {
                ss << "[" << m_itemLabels.at(i) << "] ";
            }

            ss << m_items[i] << "\n";
        }

        // End list environment
        ss << end();

        return ss.str();
    }

    /**
     * Implementation for Document class
     */
    Document::Document(DocumentType type, const std::string &title,
                       const std::string &author, const std::string &date,
                       Language language)
        : m_type(type), m_title(title), m_author(author), m_date(date), m_language(language)
    {
        // Do not load natbib by default
        
        // Add common packages used in most document types
        addPackage("inputenc", "utf8");
        addPackage("fontenc", "T1");

        // Add language support packages
        if (m_language != Language::ENGLISH)
        {
            addPackage("babel", getBabelLanguageName(m_language));
        }

        // Add special packages based on the language
        switch (m_language)
        {
        case Language::RUSSIAN:
            // Add cyrillic support for Russian
            addPackage("cyrillic");
            break;
        case Language::CHINESE:
        case Language::JAPANESE:
            // Add CJK support for Chinese and Japanese
            addPackage("xeCJK");
            break;
        case Language::ARABIC:
            // Add right-to-left support for Arabic
            addPackage("arabxetex");
            break;
        default:
            break;
        }
    }

    std::string Document::getLanguageConfiguration() const
    {
        std::stringstream ss;

        // Configure document according to language specifics
        switch (m_language)
        {
        case Language::FRENCH:
            ss << "\\frenchbsetup{StandardLayout=true}\n";
            break;
        case Language::GERMAN:
            ss << "\\selectlanguage{ngerman}\n"; // Changed from "german" to "ngerman"
            break;
        case Language::SPANISH:
            ss << "\\selectlanguage{spanish}\n";
            break;
        case Language::ITALIAN:
            ss << "\\selectlanguage{italian}\n";
            break;
        case Language::PORTUGUESE:
            ss << "\\selectlanguage{portuguese}\n";
            break;
        case Language::DUTCH:
            ss << "\\selectlanguage{dutch}\n";
            break;
        case Language::RUSSIAN:
            ss << "\\selectlanguage{russian}\n";
            break;
        case Language::CHINESE:
            ss << "\\setCJKmainfont{SimSun}\n";
            break;
        case Language::JAPANESE:
            ss << "\\setCJKmainfont{IPAMincho}\n";
            break;
        case Language::ARABIC:
            ss << "\\setmainlanguage{arabic}\n";
            break;
        case Language::ENGLISH:
        default:
            // No special configuration needed for English
            break;
        }

        return ss.str();
    }

    std::string Document::getDocumentClass() const
    {
        std::string documentClass;

        switch (m_type)
        {
        case DocumentType::ARTICLE:
            documentClass = "article";
            break;
        case DocumentType::REPORT:
            documentClass = "report";
            break;
        case DocumentType::BOOK:
            documentClass = "book";
            break;
        case DocumentType::PRESENTATION:
            documentClass = "beamer";
            break;
        default:
            documentClass = "article";
        }

        return documentClass;
    }

    std::string Document::generatePreamble() const
    {
        std::stringstream ss;

        // Document class
        ss << "\\documentclass{" << getDocumentClass() << "}\n\n";

        // Packages
        for (const auto &package : m_packages)
        {
            ss << "\\usepackage";
            if (!package.second.empty())
            {
                ss << "[" << package.second << "]";
            }
            ss << "{" << package.first << "}\n";
        }
        ss << "\n";

        // Language configuration
        ss << getLanguageConfiguration();

        // Document information
        if (!m_title.empty())
        {
            ss << "\\title{" << m_title << "}\n";
        }

        if (!m_author.empty())
        {
            ss << "\\author{" << m_author << "}\n";
        }

        if (!m_date.empty())
        {
            ss << "\\date{" << m_date << "}\n";
        }
        
        // Add theorem environment support if enabled
        if (m_theoremsEnabled)
        {
            ss << TheoremEnvironment::getTheoremSetup(m_language);
        }
        
        // Add algorithm environment support if enabled
        if (m_algorithmsEnabled)
        {
            ss << Algorithm::getAlgorithmPackages();
        }
        
        // Add bibliography configuration if a bibliography is set
        if (!m_usedCitations.empty())
        {
            ss << m_bibliography.getPreambleConfig();
        }
        
        // Add custom preamble content
        for (const auto &content : m_customPreamble)
        {
            ss << content << "\n";
        }

        ss << "\n";

        return ss.str();
    }

    std::string Document::generateDocument() const
    {
        std::stringstream ss;

        // Begin document
        ss << "\\begin{document}\n\n";

        // Generate title page if title is set
        if (!m_title.empty())
        {
            ss << "\\maketitle\n\n";
        }

        // Add raw content
        for (const auto &content : m_rawContent)
        {
            ss << content << "\n\n";
        }

        // Add sections
        for (const auto &section : m_sections)
        {
            ss << section.generate() << "\n";
        }

        // Add environments
        for (const auto &env : m_environments)
        {
            ss << env->generate() << "\n";
        }
        
        // Add bibliography if citations are used
        if (!m_usedCitations.empty())
        {
            ss << m_bibliography.getIncludeCommands() << "\n";
        }

        // End document
        ss << "\\end{document}\n";

        return ss.str();
    }

    bool Document::saveToFile(const std::string &Path, const std::string &filePath) const
    {
        // Create directory if it doesn't exist and Path is not empty
        if (!Path.empty())
        {
            // Create directory if it doesn't exist
            std::filesystem::path dirPath(Path);
            if (!std::filesystem::exists(dirPath))
            {
                std::filesystem::create_directories(dirPath);
            }
        }
        // Combine Path and filePath
        std::filesystem::path fullPath = Path.empty() ? filePath : (Path + "/" + filePath);

        // Open file for writing
        std::ofstream outFile(fullPath);
        if (!outFile.is_open())
        {
            return false;
        }

        outFile << generate();
        outFile.close();

        return true;
    }

    std::string Document::generate() const
    {
        return generatePreamble() + generateDocument();
    }

    std::shared_ptr<Figure> Document::addFigure(const std::string &imagePath, 
                                     const std::string &caption,
                                     const std::string &label, 
                                     const std::string &width,
                                     const std::string &position)
    {
        // Create the Figure object with the provided parameters
        auto figure = std::make_shared<Figure>(imagePath, position);
        
        // Configure the properties of the figure
        figure->setCaption(caption);
        figure->setWidth(width);
        
        if (!label.empty()) {
            figure->setLabel(label);
        }
        
        // Automatically add the graphicx package required for figures
        addPackage("graphicx");
        
        // Add the figure to the document environments
        addEnvironment(figure);
        
        return figure;
    }

    std::shared_ptr<Table> Document::addTable(const std::vector<std::string> &headers,
                                   const std::string &caption,
                                   const std::string &label,
                                   const std::string &position)
    {
        // Create the table with the specified headers and position
        auto table = std::make_shared<Table>(headers, position);
        
        // Configure the properties of the table
        table->setCaption(caption);
        
        if (!label.empty()) {
            table->setLabel(label);
        }
        
        // Add the table to the document environments
        addEnvironment(table);
        
        return table;
    }

    std::shared_ptr<List> Document::addList(List::ListType type)
    {
        // Create a new List object with the specified type
        auto list = std::make_shared<List>(type);
        
        // Add the list to the document environments
        addEnvironment(list);
        
        return list;
    }

    std::shared_ptr<Equation> Document::addEquation(const std::string &content,
                                           const std::string &label,
                                           bool numbered)
    {
        // Create a new equation with the numbered parameter
        auto equation = std::make_shared<Equation>(numbered);
        
        // Configure the content and optionally the label
        equation->setContent(content);
        
        if (!label.empty()) {
            equation->setLabel(label);
        }
        
        // Ensure the amsmath package is loaded
        addPackage("amsmath");
        
        // Add the equation to the document environments
        addEnvironment(equation);
        
        return equation;
    }

    std::string Document::addInlineEquation(const std::string &content)
    {
        // Inline equations use $ delimiters in LaTeX
        // Ensure the amsmath package is loaded for some math commands
        addPackage("amsmath");
        
        return "$" + content + "$";
    }

    std::shared_ptr<Algorithm> Document::addAlgorithm(const std::string &caption,
                                             const std::string &label)
    {
        // Create a new algorithm
        auto algorithm = std::make_shared<Algorithm>(caption);
        
        // Add a label if specified
        if (!label.empty()) {
            algorithm->setLabel(label);
        }
        
        // Enable algorithm support
        enableAlgorithms();
        
        // Add the algorithm to the document environments
        addEnvironment(algorithm);
        
        return algorithm;
    }

    std::shared_ptr<TheoremEnvironment> Document::addTheorem(TheoremEnvironment::Type type,
                                                   const std::string &content,
                                                   const std::string &title)
    {
        // Create a new theorem environment
        auto theorem = std::make_shared<TheoremEnvironment>(type, content, title);
        
        // Enable theorem support
        enableTheorems();
        
        // Add the theorem to the document environments
        addEnvironment(theorem);
        
        return theorem;
    }

    /**
     * Implementation for Article class
     */
    std::string Article::generatePreamble() const
    {
        std::stringstream ss;

        // Get base preamble
        ss << Document::generatePreamble();
        
        // Configure listings to handle accented characters correctly
        ss << "\\lstset{\n";
        ss << "  basicstyle=\\small\\ttfamily,\n";
        ss << "  keywordstyle=\\color{blue}\\bfseries,\n";
        ss << "  commentstyle=\\color{green!60!black}\\itshape,\n";
        ss << "  stringstyle=\\color{purple},\n";
        ss << "  frame=single,\n";
        ss << "  breaklines=true,\n";
        ss << "  showstringspaces=false,\n";
        ss << "  inputencoding=utf8,\n";
        ss << "  extendedchars=true,\n";
        ss << "  literate={é}{{\\'e}}1 {è}{{\\`e}}1 {ê}{{\\^e}}1 {ë}{{\\\"e}}1\n";
        ss << "           {à}{{\\`a}}1 {â}{{\\^a}}1 {ä}{{\\\"a}}1\n";
        ss << "           {î}{{\\^i}}1 {ï}{{\\\"i}}1\n";
        ss << "           {ô}{{\\^o}}1 {ö}{{\\\"o}}1\n";
        ss << "           {ù}{{\\`u}}1 {û}{{\\^u}}1 {ü}{{\\\"u}}1\n";
        ss << "           {ç}{{\\c c}}1\n";
        ss << "}\n\n";
        
        // Add custom preamble content
        for (const auto &content : m_customPreamble)
        {
            ss << content << "\n";
        }
        
        // Define the keywords command according to the language
        if (!m_keywords.empty())
        {
            // Define the \keywords command with an appropriate name according to the language
            std::string keywordsTitle;
            switch (m_language)
            {
            case Language::FRENCH:
                keywordsTitle = "Mots-clés:";
                break;
            case Language::GERMAN:
                keywordsTitle = "Schlüsselwörter:";
                break;
            case Language::SPANISH:
                keywordsTitle = "Palabras clave:";
                break;
            case Language::ITALIAN:
                keywordsTitle = "Parole chiave:";
                break;
            case Language::PORTUGUESE:
                keywordsTitle = "Palavras-chave:";
                break;
            case Language::DUTCH:
                keywordsTitle = "Trefwoorden:";
                break;
            case Language::RUSSIAN:
                keywordsTitle = "Ключевые слова:";
                break;
            case Language::CHINESE:
                keywordsTitle = "关键词:";
                break;
            case Language::JAPANESE:
                keywordsTitle = "キーワード:";
                break;
            case Language::ARABIC:
                keywordsTitle = "الكلمات المفتاحية:";
                break;
            case Language::ENGLISH:
            default:
                keywordsTitle = "Keywords:";
                break;
            }
            
            ss << "\\providecommand{\\keywords}[1]{\\par\\noindent\\textbf{" << keywordsTitle << "} #1}\n\n";
        }
        
        // Add index configuration if enabled
        if (m_includeIndex)
        {
            // Choose the index title according to the language
            std::string indexTitle;
            switch (m_language)
            {
            case Language::FRENCH:
                indexTitle = "Index alphabétique";
                break;
            case Language::GERMAN:
                indexTitle = "Alphabetischer Index";
                break;
            case Language::SPANISH:
                indexTitle = "Índice alfabético";
                break;
            case Language::ITALIAN:
                indexTitle = "Indice alfabetico";
                break;
            case Language::PORTUGUESE:
                indexTitle = "Índice alfabético";
                break;
            case Language::DUTCH:
                indexTitle = "Alfabetische index";
                break;
            case Language::RUSSIAN:
                indexTitle = "Алфавитный указатель";
                break;
            case Language::CHINESE:
                indexTitle = "索引";
                break;
            case Language::JAPANESE:
                indexTitle = "索引";
                break;
            case Language::ARABIC:
                indexTitle = "فهرس";
                break;
            case Language::ENGLISH:
            default:
                indexTitle = "Alphabetical Index";
                break;
            }

            ss << "\\makeindex[columns=2, title=" << indexTitle << ", intoc]\n\n";
        }

        return ss.str();
    }

    void Article::setBibliography(const Bibliography& bibliography)
    {
        m_bibliography = bibliography;
    
        // Automatically add the .bib file to the output directory
        if (!m_bibliography.getBibFile().empty()) {
            createBibFile();
        }
    }

    void Article::createBibFile() const
    {
        std::string outputPath = "output/";
        std::string bibFilePath = outputPath + m_bibliography.getBibFile() + ".bib";
        
        // Create the output directory if it doesn't exist
        std::filesystem::path dirPath(outputPath);
        if (!std::filesystem::exists(dirPath))
        {
            std::filesystem::create_directories(dirPath);
        }
        
        // Create a sample bib file if not existing
        if (!std::filesystem::exists(bibFilePath))
        {
            std::ofstream bibFile(bibFilePath);
            if (bibFile.is_open())
            {
                bibFile << "@article{smith2023,\n";
                bibFile << "  author  = {John Smith},\n";
                bibFile << "  title   = {Introduction to LaTeX Programming},\n";
                bibFile << "  journal = {Journal of Document Engineering},\n";
                bibFile << "  year    = {2023},\n";
                bibFile << "  volume  = {42},\n";
                bibFile << "  number  = {1},\n";
                bibFile << "  pages   = {123--456}\n";
                bibFile << "}\n";
                
                bibFile.close();
            }
        }
    }

    std::string Article::generateDocument() const
    {
        std::stringstream ss;

        // Begin document
        ss << "\\begin{document}\n\n";

        // Generate title page if title is set
        if (!m_title.empty())
        {
            ss << "\\maketitle\n\n";
            
            // Add keywords after the title page
            if (!m_keywords.empty())
            {
                ss << "\\keywords{";
                for (size_t i = 0; i < m_keywords.size(); ++i)
                {
                    ss << m_keywords[i];
                    if (i < m_keywords.size() - 1)
                    {
                        ss << ", ";
                    }
                }
                ss << "}\n\n";
            }
        }

        // Abstract if set
        if (!m_abstract.empty())
        {
            ss << "\\begin{abstract}\n"
               << m_abstract << "\n\\end{abstract}\n\n";
        }

        // Table of contents if requested
        if (m_includeTableOfContents)
        {
            ss << "\\tableofcontents\n\\clearpage\n\n";
        }

        // Add raw content
        for (const auto &content : m_rawContent)
        {
            ss << content << "\n\n";
        }

        // Add sections
        for (const auto &section : m_sections)
        {
            ss << section.generate() << "\n";
        }

        // Add environments
        for (const auto &env : m_environments)
        {
            ss << env->generate() << "\n";
        }
            
        // Add bibliography if citations are used
        if (!m_usedCitations.empty())
        {
            ss << m_bibliography.getIncludeCommands() << "\n";
        }

        // End document
        ss << "\\end{document}\n";

        return ss.str();
    }

    /**
     * Implementation for Report class
     */
    std::string Report::generatePreamble() const
    {
        std::stringstream ss;

        // Get base preamble
        ss << Document::generatePreamble();

        return ss.str();
    }

    std::string Report::generateDocument() const
    {
        std::stringstream ss;

        // Begin document
        ss << "\\begin{document}\n\n";

        // Generate title page if title is set
        if (!m_title.empty())
        {
            ss << "\\maketitle\n\n";
        }

        // Abstract if set
        if (!m_abstract.empty())
        {
            ss << "\\begin{abstract}\n"
               << m_abstract << "\n\\end{abstract}\n\n";
        }

        // Table of contents if requested
        if (m_includeTableOfContents)
        {
            ss << "\\tableofcontents\n\\clearpage\n\n";
        }

        // List of figures if requested
        if (m_includeListOfFigures)
        {
            ss << "\\listoffigures\n\\clearpage\n\n";
        }

        // List of tables if requested
        if (m_includeListOfTables)
        {
            ss << "\\listoftables\n\\clearpage\n\n";
        }

        // Add raw content
        for (const auto &content : m_rawContent)
        {
            ss << content << "\n\n";
        }

        // Add sections
        for (const auto &section : m_sections)
        {
            ss << section.generate() << "\n";
        }

        // Add environments
        for (const auto &env : m_environments)
        {
            ss << env->generate() << "\n";
        }

        // End document
        ss << "\\end{document}\n";

        return ss.str();
    }

    /**
     * Implementation for Book class
     */
    std::string Book::generatePreamble() const
    {
        std::stringstream ss;

        // Get base preamble
        ss << Document::generatePreamble();

        // Add specific configurations for books
        // Add the makeindex command in the preamble if the index is enabled
        if (m_includeIndex)
        {
            // Choose the index title according to the language
            std::string indexTitle;
            switch (m_language)
            {
            case Language::FRENCH:
                indexTitle = "Index alphabétique";
                break;
            case Language::GERMAN:
                indexTitle = "Alphabetischer Index";
                break;
            case Language::SPANISH:
                indexTitle = "Índice alfabético";
                break;
            case Language::ITALIAN:
                indexTitle = "Indice alfabetico";
                break;
            case Language::PORTUGUESE:
                indexTitle = "Índice alfabético";
                break;
            case Language::DUTCH:
                indexTitle = "Alfabetische index";
                break;
            case Language::RUSSIAN:
                indexTitle = "Алфавитный указатель";
                break;
            case Language::CHINESE:
                indexTitle = "索引";
                break;
            case Language::JAPANESE:
                indexTitle = "索引";
                break;
            case Language::ARABIC:
                indexTitle = "فهرس";
                break;
            case Language::ENGLISH:
            default:
                indexTitle = "Alphabetical Index";
                break;
            }

            ss << "\\makeindex[columns=2, title=" << indexTitle << ", intoc]\n\n";
        }

        // Define abstract environment for book class if not already defined
        ss << "\\providecommand{\\abstractname}{Abstract}\n";
        ss << "\\ifdefined\\abstract\\else\n";
        ss << "  \\newenvironment{abstract}{\\chapter*{\\abstractname}}{}\n";
        ss << "\\fi\n";

        return ss.str();
    }

    std::string Book::generateDocument() const
    {
        std::stringstream ss;

        // Begin document
        ss << "\\begin{document}\n\n";

        // Generate title page
        ss << "\\maketitle\n\n";

        // Abstract if present
        if (!m_abstract.empty())
        {
            ss << "\\begin{abstract}\n"
               << m_abstract << "\n\\end{abstract}\n\n";
        }

        // Table of contents, list of figures, list of tables
        if (m_includeTableOfContents)
        {
            ss << "\\tableofcontents\n\n";
        }

        if (m_includeListOfFigures)
        {
            ss << "\\listoffigures\n\n";
        }

        if (m_includeListOfTables)
        {
            ss << "\\listoftables\n\n";
        }

        // Parts and chapters
        for (size_t i = 0; i < m_parts.size(); ++i)
        {
            ss << "\\part{" << m_parts[i] << "}\n\n";

            auto it = m_partChapters.find(i);
            if (it != m_partChapters.end())
            {
                for (const auto &chapter : it->second)
                {
                    ss << chapter.generate() << "\n";
                }
            }
        }

        // Regular sections (outside parts)
        for (const auto &section : m_sections)
        {
            ss << section.generate() << "\n";
        }

        // Environments
        for (const auto &env : m_environments)
        {
            ss << env->generate() << "\n";
        }

        // Raw content
        for (const auto &content : m_rawContent)
        {
            ss << content << "\n\n";
        }

        // Appendices
        if (!m_appendices.empty())
        {
            ss << "\\appendix\n\n";
            for (const auto &appendix : m_appendices)
            {
                ss << appendix.generate() << "\n";
            }
        }

        // Index if enabled
        if (m_includeIndex)
        {
            ss << "\\printindex\n\n";
        }

        // End of document
        ss << "\\end{document}\n";

        return ss.str();
    }

    /**
     * Implementation for Presentation class
     */
    std::string Presentation::getThemeName() const
    {
        switch (m_theme)
        {
        case Theme::BERKELEY:
            return "Berkeley";
        case Theme::MADRID:
            return "Madrid";
        case Theme::ANTIBES:
            return "Antibes";
        case Theme::COPENHAGEN:
            return "Copenhagen";
        case Theme::BERLIN:
            return "Berlin";
        case Theme::MANHATTAN:
            return "Manhattan";
        case Theme::WARSAW:
            return "Warsaw";
        case Theme::SINGAPORE:
            return "Singapore";
        case Theme::DEFAULT:
        default:
            return "default";
        }
    }

    std::string Presentation::getColorThemeName() const
    {
        switch (m_colorTheme)
        {
        case ColorTheme::BEAVER:
            return "beaver";
        case ColorTheme::CRANE:
            return "crane";
        case ColorTheme::DOLPHIN:
            return "dolphin";
        case ColorTheme::DOVE:
            return "dove";
        case ColorTheme::FLY:
            return "fly";
        case ColorTheme::SEAGULL:
            return "seagull";
        case ColorTheme::WOLVERINE:
            return "wolverine";
        case ColorTheme::DEFAULT:
        default:
            return "default";
        }
    }

    std::string Presentation::getTransitionName() const
    {
        switch (m_transition)
        {
        case Transition::FADE:
            return "transparent";
        case Transition::PUSH:
            return "push";
        case Transition::COVER:
            return "dynamic";
        case Transition::UNCOVER:
            return "invisible";
        case Transition::SPLIT:
            return "split";
        case Transition::BLINDS:
            return "dynamic";
        case Transition::WIPE:
            return "dynamic";
        case Transition::NONE:
        default:
            return "invisible";
        }
    }

    std::string Presentation::getLevelCommand(Section::Level level) const
    {
        switch (level)
        {
        case Section::Level::SECTION:
            return "\\section";
        case Section::Level::SUBSECTION:
            return "\\subsection";
        case Section::Level::SUBSUBSECTION:
            return "\\subsubsection";
        default:
            return "\\section";
        }
    }

    std::string Presentation::generatePreamble() const
    {
        std::stringstream ss;

        // Document class for beamer
        ss << "\\documentclass{beamer}\n\n";

        // Packages
        for (const auto &package : m_packages)
        {
            ss << "\\usepackage";
            if (!package.second.empty())
            {
                ss << "[" << package.second << "]";
            }
            ss << "{" << package.first << "}\n";
        }
        ss << "\n";

        // Configuration for listings with accented character support
        ss << "\\lstset{\n";
        ss << "  basicstyle=\\small\\ttfamily,\n";
        ss << "  breaklines=true,\n";
        ss << "  inputencoding=utf8,\n";
        ss << "  extendedchars=true,\n";
        ss << "  literate={é}{{\\'e}}1 {è}{{\\`e}}1 {ê}{{\\^e}}1 {ë}{{\\\"e}}1\n";
        ss << "           {à}{{\\`a}}1 {â}{{\\^a}}1 {ä}{{\\\"a}}1\n";
        ss << "           {î}{{\\^i}}1 {ï}{{\\\"i}}1\n";
        ss << "           {ô}{{\\^o}}1 {ö}{{\\\"o}}1\n";
        ss << "           {ù}{{\\`u}}1 {û}{{\\^u}}1 {ü}{{\\\"u}}1\n";
        ss << "           {ç}{{\\c c}}1\n";
        ss << "}\n\n";

        // Language configuration
        ss << getLanguageConfiguration();

        // Beamer theme
        if (m_theme != Theme::DEFAULT)
        {
            ss << "\\usetheme{" << getThemeName() << "}\n";
        }

        // Beamer color theme
        if (m_colorTheme != ColorTheme::DEFAULT)
        {
            ss << "\\usecolortheme{" << getColorThemeName() << "}\n";
        }

        // Slide transition
        if (m_transition != Transition::NONE)
        {
            ss << "\\setbeamercovered{" << getTransitionName() << "}\n";
        }

        // Navigation bar
        if (!m_showNavigation)
        {
            ss << "\\setbeamertemplate{navigation symbols}{}\n";
        }

        // Document information
        if (!m_title.empty())
        {
            ss << "\\title{" << m_title << "}\n";
        }

        if (!m_subtitle.empty())
        {
            ss << "\\subtitle{" << m_subtitle << "}\n";
        }

        if (!m_author.empty())
        {
            ss << "\\author{" << m_author << "}\n";
        }

        if (!m_institute.empty())
        {
            ss << "\\institute{" << m_institute << "}\n";
        }

        if (!m_date.empty())
        {
            ss << "\\date{" << m_date << "}\n";
        }

        ss << "\n";

        return ss.str();
    }

    std::string Presentation::generateDocument() const
    {
        std::stringstream ss;

        // Begin document
        ss << "\\begin{document}\n\n";

        // Title frame
        if (!m_title.empty())
        {
            ss << "\\begin{frame}\n";
            ss << "\\titlepage\n";
            ss << "\\end{frame}\n\n";
        }

        // Table of contents frame
        ss << "\\begin{frame}{Plan}\n";
        ss << "\\tableofcontents\n";
        ss << "\\end{frame}\n\n";

        // Add raw content
        for (const auto &content : m_rawContent)
        {
            ss << content << "\n\n";
        }

        // Add structure (sections, subsections...)
        for (const auto &structureItem : m_structure)
        {
            Section::Level level;
            std::string title;
            bool createFrame;
            std::tie(level, title, createFrame) = structureItem;

            // Add the section/subsection command
            ss << getLevelCommand(level) << "{" << title << "}\n\n";

            // Create a title slide for this section if requested
            if (createFrame)
            {
                ss << "\\begin{frame}\n";
                ss << "\\";

                // Use the appropriate command for the slide title
                switch (level)
                {
                case Section::Level::SECTION:
                    ss << "sectionpage";
                    break;
                case Section::Level::SUBSECTION:
                    ss << "subsectionpage";
                    break;
                case Section::Level::SUBSUBSECTION:
                default:
                    // For subsubsections, use a simple title
                    ss << "begin{center}\\Large " << title << "\\end{center}";
                    break;
                }

                ss << "\n\\end{frame}\n\n";
            }
        }

        // Add slides
        for (const auto &slide : m_slides)
        {
            // Check if the slide contains code (lstlisting) to add the fragile option
            bool needsFragile = false;
            for (const auto &content : slide.second)
            {
                if (content.find("\\begin{lstlisting}") != std::string::npos)
                {
                    needsFragile = true;
                    break;
                }
            }

            if (needsFragile)
            {
                ss << "\\begin{frame}[fragile]{" << slide.first << "}\n";
            }
            else
            {
                ss << "\\begin{frame}{" << slide.first << "}\n";
            }

            for (const auto &content : slide.second)
            {
                ss << content << "\n";
            }
            ss << "\\end{frame}\n\n";
        }

        // Add sections from the Document class - each treated as a regular section
        for (const auto &section : m_sections)
        {
            // Extract the level and title of the section
            Section::Level level = section.Level::SECTION; // Default level
            std::string title = "Section";
            std::string sectionContent = section.generate();

            // Parse the content to extract the title
            size_t startPos = sectionContent.find("{");
            size_t endPos = sectionContent.find("}");
            if (startPos != std::string::npos && endPos != std::string::npos)
            {
                title = sectionContent.substr(startPos + 1, endPos - startPos - 1);
            }

            // Add a Beamer section
            ss << "\\section{" << title << "}\n\n";

            // Add a slide with the section content
            ss << "\\begin{frame}{" << title << "}\n";

            // If the content contains equations, ensure they are properly formatted
            std::string content = sectionContent.substr(endPos + 1);
            content = sanitizeMathContent(content);

            ss << content;
            ss << "\\end{frame}\n\n";
        }

        // Add environments - each treated as a separate frame
        for (const auto &env : m_environments)
        {
            // Check if the environment contains code (lstlisting) to add the fragile option
            std::string envContent = env->generate();
            if (envContent.find("\\begin{lstlisting}") != std::string::npos)
            {
                ss << "\\begin{frame}[fragile]\n";
            }
            else
            {
                ss << "\\begin{frame}\n";
            }
            ss << envContent << "\n";
            ss << "\\end{frame}\n\n";
        }

        // End document
        ss << "\\end{document}\n";

        return ss.str();
    }

    /**
     * Implementation for Bibliography class
     */
    std::string Bibliography::getStyleName() const
    {
        switch (m_style)
        {
        case BibStyle::PLAIN:
            return "plain";
        case BibStyle::ALPHA:
            return "alpha";
        case BibStyle::ABBRV:
            return "abbrv";
        case BibStyle::ACM:
            return "acm";
        case BibStyle::IEEE:
            return "ieeetr";
        case BibStyle::APA:
            return "apalike";
        case BibStyle::CHICAGO:
            return "chicago";
        case BibStyle::MLA:
            return "mla";
        case BibStyle::HARVARD:
            return "harvard";
        case BibStyle::CUSTOM:
            return m_customStyle;
        default:
            return "plain";
        }
    }

    std::string Bibliography::getPreambleConfig() const
    {
        // No need to configure natbib since we use standard LaTeX bibliography
        return "";
    }

    std::string Bibliography::getIncludeCommands(const std::string& title) const
    {
        std::stringstream ss;
        
        // Get the appropriate title based on language, if not provided
        std::string bibTitle = title;
        if (bibTitle.empty())
        {
            // Default title is "References" or appropriate translation
            bibTitle = "References";
        }
        
        // Add bibliography commands
        ss << "\n\\bibliographystyle{" << getStyleName() << "}\n";
        ss << "\\bibliography{" << m_bibFile << "}\n";
        
        return ss.str();
    }

    std::string Bibliography::getBibFile() const
    {
        return m_bibFile;
    }

    bool Bibliography::generateBibFile(const std::string &outputDir) const
    {
        // If the bibliography does not contain manual entries, nothing to generate
        if (m_entries.empty()) {
            return false;
        }
        
        // Determine the file path
        std::string filePath = m_bibFile + ".bib";
        if (!outputDir.empty()) {
            // Create the output directory if it doesn't exist
            std::filesystem::path dirPath(outputDir);
            if (!std::filesystem::exists(dirPath)) {
                std::filesystem::create_directories(dirPath);
            }
            filePath = outputDir + "/" + filePath;
        }
        
        // Open the file for writing
        std::ofstream bibFile(filePath);
        if (!bibFile.is_open()) {
            return false;
        }
        
        // Write all bibliography entries
        for (const auto &entry : m_entries) {
            bibFile << entry.generate() << "\n";
        }
        
        bibFile.close();
        return true;
    }

    /**
     * Implementation for BibEntry class
     */
    std::string BibEntry::getTypeString(EntryType type)
    {
        switch (type)
        {
        case EntryType::ARTICLE:
            return "article";
        case EntryType::BOOK:
            return "book";
        case EntryType::INPROCEEDINGS:
            return "inproceedings";
        case EntryType::TECHREPORT:
            return "techreport";
        case EntryType::PHDTHESIS:
            return "phdthesis";
        case EntryType::MASTERSTHESIS:
            return "mastersthesis";
        case EntryType::MISC:
        default:
            return "misc";
        }
    }

    std::string BibEntry::generate() const
    {
        std::stringstream ss;
        
        // Start of the bibliography entry
        ss << "@" << getTypeString(m_type) << "{" << m_key << ",\n";
        
        // Add fields
        for (auto it = m_fields.begin(); it != m_fields.end(); ++it)
        {
            ss << "  " << it->first << " = {" << it->second << "}";
            
            // Add a comma except for the last field
            if (std::next(it) != m_fields.end())
            {
                ss << ",";
            }
            ss << "\n";
        }
        
        // End of the bibliography entry
        ss << "}\n";
        
        return ss.str();
    }

    /**
     * Implementation for TheoremEnvironment class
     */
    std::string TheoremEnvironment::getEnvironmentName(Type type)
    {
        switch (type)
        {
        case Type::THEOREM:
            return "theorem";
        case Type::LEMMA:
            return "lemma";
        case Type::PROPOSITION:
            return "proposition";
        case Type::COROLLARY:
            return "corollary";
        case Type::DEFINITION:
            return "definition";
        case Type::EXAMPLE:
            return "example";
        case Type::REMARK:
            return "remark";
        case Type::PROOF:
            return "proof";
        case Type::CUSTOM:
            return "customtheorem";
        default:
            return "theorem";
        }
    }

    std::string TheoremEnvironment::generate() const
    {
        std::stringstream ss;

        // Begin the theorem environment
        ss << "\\begin{" << m_name << "}";
        
        // Add title if provided
        if (!m_title.empty())
        {
            ss << "[" << m_title << "]";
        }
        
        ss << "\n";
        
        // Add content
        ss << m_content << "\n";
        
        // End the theorem environment
        ss << "\\end{" << m_name << "}\n";
        
        return ss.str();
    }

    std::string TheoremEnvironment::getTheoremSetup(Language language)
    {
        std::stringstream ss;
        
        // Add necessary packages
        ss << "\\usepackage{amsthm}\n";
        
        // Define theorem styles
        ss << "\\theoremstyle{plain}\n";
        
        // Set up theorem environment names based on language
        std::string theorem, lemma, proposition, corollary, definition, example, remark, proof;
        
        switch (language)
        {
        case Language::FRENCH:
            theorem = "Théorème";
            lemma = "Lemme";
            proposition = "Proposition";
            corollary = "Corollaire";
            definition = "Définition";
            example = "Exemple";
            remark = "Remarque";
            proof = "Preuve";
            break;
        case Language::GERMAN:
            theorem = "Satz";
            lemma = "Lemma";
            proposition = "Behauptung";
            corollary = "Korollar";
            definition = "Definition";
            example = "Beispiel";
            remark = "Bemerkung";
            proof = "Beweis";
            break;
        case Language::SPANISH:
            theorem = "Teorema";
            lemma = "Lema";
            proposition = "Proposición";
            corollary = "Corolario";
            definition = "Definición";
            example = "Ejemplo";
            remark = "Observación";
            proof = "Demostración";
            break;
        case Language::ITALIAN:
            theorem = "Teorema";
            lemma = "Lemma";
            proposition = "Proposizione";
            corollary = "Corollario";
            definition = "Definizione";
            example = "Esempio";
            remark = "Osservazione";
            proof = "Dimostrazione";
            break;
        case Language::ENGLISH:
        default:
            theorem = "Theorem";
            lemma = "Lemma";
            proposition = "Proposition";
            corollary = "Corollary";
            definition = "Definition";
            example = "Example";
            remark = "Remark";
            proof = "Proof";
            break;
        }
        
        // Define theorem-like environments
        ss << "\\newtheorem{theorem}{" << theorem << "}\n";
        ss << "\\newtheorem{lemma}[theorem]{" << lemma << "}\n";
        ss << "\\newtheorem{proposition}[theorem]{" << proposition << "}\n";
        ss << "\\newtheorem{corollary}[theorem]{" << corollary << "}\n";
        
        // Define definition-like environments
        ss << "\\theoremstyle{definition}\n";
        ss << "\\newtheorem{definition}{" << definition << "}\n";
        ss << "\\newtheorem{example}{" << example << "}\n";
        
        // Define remark-like environments
        ss << "\\theoremstyle{remark}\n";
        ss << "\\newtheorem{remark}{" << remark << "}\n";
        
        // Redefine proof environment
        ss << "\\renewcommand{\\proofname}{" << proof << "}\n";
        
        return ss.str();
    }

    /**
     * Implementation for Algorithm class
     */
    std::string Algorithm::generate() const
    {
        std::stringstream ss;
        
        // Begin algorithm environment
        ss << "\\begin{algorithm}\n";
        
        // Add caption if provided
        if (!m_caption.empty())
        {
            ss << "\\caption{" << m_caption << "}\n";
        }
        
        // Add label if provided
        if (!m_label.empty())
        {
            ss << "\\label{" << m_label << "}\n";
        }
        
        // Begin algorithmic environment
        ss << "\\begin{algorithmic}[1]\n";
        
        // Add lines with appropriate indentation
        for (const auto& line : m_lines)
        {
            // Add indentation
            for (int i = 0; i < line.second; ++i)
            {
                ss << "    ";
            }
            
            // Add line content
            ss << line.first << "\n";
        }
        
        // End algorithmic environment
        ss << "\\end{algorithmic}\n";
        
        // End algorithm environment
        ss << "\\end{algorithm}\n";
        
        return ss.str();
    }

    std::string Algorithm::getAlgorithmPackages()
    {
        // Use algpseudocode instead of algorithmic for better compatibility
        return "\\usepackage{algorithm}\n"
               "\\usepackage{algpseudocode}\n";
    }




} // namespace LatexGen