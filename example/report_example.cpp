#include "latexgen.h"
#include <iostream>
#include <memory>

using namespace LatexGen;

/**
 * Exemple de génération d'un rapport technique avec LatexGenC++
 */
int main() {
    std::cout << "Création d'un exemple de rapport LaTeX..." << std::endl;
    
    // Création du document rapport
    Report rapport("Mon Rapport Technique", "Jane Smith", "\\today");
    rapport.setAbstract("Ce rapport présente les résultats d'une étude technique sur la génération de documents LaTeX.");
    
    // Activation des tables des matières, figures et tableaux
    rapport.includeTableOfContents(true);
    rapport.includeListOfFigures(true);
    rapport.includeListOfTables(true);
    
    // Ajout de paquets supplémentaires
    rapport.addPackage("listings");
    rapport.addPackage("xcolor");
    rapport.addPackage("appendix");
    
    // Création de chapitres pour le rapport
    Section chapitre1("Introduction", Section::Level::CHAPTER);
    chapitre1.addContent("Ce rapport présente une bibliothèque C++ pour la génération de documents LaTeX.");
    chapitre1.addContent("Nous explorerons ses fonctionnalités et son architecture.");
    
    Section chapitre2("Contexte et objectifs", Section::Level::CHAPTER);
    chapitre2.addContent("La génération automatique de documents est un domaine important pour de nombreuses applications.");
    
    // Ajout d'une section à l'intérieur du chapitre 2
    Section contexte("Contexte technique", Section::Level::SECTION);
    contexte.addContent("Les documents LaTeX sont largement utilisés dans le monde académique et scientifique.");
    chapitre2.addContent(contexte.generate());
    
    Section objectifs("Objectifs du projet", Section::Level::SECTION);
    objectifs.addContent("L'objectif principal est de faciliter la création programmatique de documents LaTeX.");
    chapitre2.addContent(objectifs.generate());
    
    Section chapitre3("Implémentation", Section::Level::CHAPTER);
    chapitre3.addContent("La bibliothèque est implémentée en C++ avec une approche orientée objet.");
    
    // Sous-sections d'implémentation
    Section classes_impl("Classes principales", Section::Level::SECTION);
    
    // Ajout d'une liste en utilisant la nouvelle méthode addList
    auto classes = rapport.addList(List::ListType::ITEMIZE);
    classes->addItem("Document : classe de base pour tous les types de documents");
    classes->addItem("Article : pour les articles scientifiques");
    classes->addItem("Report : pour les rapports techniques");
    classes->addItem("Book : pour les livres");
    classes->addItem("Presentation : pour les présentations Beamer");

    classes_impl.addContent("Voici les principales classes de notre bibliothèque :");
    classes_impl.addContent(classes->generate());
    
    chapitre3.addContent(classes_impl.generate());
    
    Section usage("Exemples d'utilisation", Section::Level::SECTION);
    usage.addContent("Voici comment utiliser notre bibliothèque :");
    usage.addContent("\\begin{lstlisting}[language=C++]\n"
                    "Article doc(\"Titre\", \"Auteur\");\n"
                    "Section intro(\"Introduction\");\n"
                    "doc.addSection(intro);\n"
                    "doc.saveToFile(\"document.tex\");\n"
                    "\\end{lstlisting}");
    chapitre3.addContent(usage.generate());
    
    Section chapitre4("Résultats", Section::Level::CHAPTER);
    chapitre4.addContent("Les tests montrent que notre bibliothèque est facile à utiliser et produit des documents LaTeX valides.");
    
    // Ajout d'une figure en utilisant la nouvelle méthode addFigure
    auto figure = rapport.addFigure(
        "architecture.png",                          // Chemin de l'image
        "Architecture de la bibliothèque LatexGenCpp", // Légende
        "fig:architecture",                          // Label pour référence
        "1.0\\textwidth",                            // Largeur de l'image
        "htbp"                                       // Position (here, top, bottom, page)
    );
    
    // Ajout d'une équation avec la nouvelle méthode addEquation
    auto equation = rapport.addEquation(
        "f(x) = \\int_{a}^{b} g(x) \\, dx",   // Contenu de l'équation
        "eq:formule",                          // Label pour référence
        true                                   // Équation numérotée
    );
    
    chapitre4.addContent("La formule mathématique \\ref{eq:formule} montre un exemple d'intégrale.");
    
    // Ajout d'un algorithme avec la nouvelle méthode addAlgorithm
    auto algorithme = rapport.addAlgorithm(
        "Recherche binaire",                   // Légende
        "algo:recherche"                       // Label
    );
    
    // Configuration de l'algorithme
    algorithme->addFunction("BinarySearch", "A : tableau d'entiers, x : entier", 0);
    algorithme->addLine("left = 0", 1);
    algorithme->addLine("right = length(A) - 1", 1);
    algorithme->addWhileLoop("left <= right", 1);
    algorithme->addLine("mid = (left + right) / 2", 2);
    algorithme->addIf("A[mid] == x", 2);
    algorithme->addReturn("mid", 3);
    algorithme->addElseIf("A[mid] < x", 2);
    algorithme->addLine("left = mid + 1", 3);
    algorithme->addElse(2);
    algorithme->addLine("right = mid - 1", 3);
    algorithme->addEnd("If", 2);
    algorithme->addEnd("While", 1);
    algorithme->addReturn("-1", 1);
    algorithme->addFunctionEnd(0);
    
    chapitre4.addContent("L'algorithme \\ref{algo:recherche} présente une implémentation de la recherche binaire.");
    
    // Ajout d'une équation
    auto equation_old = std::make_shared<Equation>();
    equation_old->setContent("f(x) = \\int_{a}^{b} g(x) \\, dx");
    equation_old->setLabel("eq:formule");
    
    // Ajout d'un tableau en utilisant la nouvelle méthode addTable
    std::vector<std::string> headers = {"Classe", "Description", "Utilisation"};
    auto tableau = rapport.addTable(
        headers,                       // En-têtes des colonnes
        "Classes principales de la bibliothèque", // Légende
        "tab:classes",                 // Label pour référence
        "htbp"                         // Position (here, top, bottom, page)
    );
    // Ajout des lignes au tableau
    tableau->addRow({"Document", "Classe de base", "Utilisée comme parent"});
    tableau->addRow({"Article", "Pour les articles", "Publication scientifique"});
    tableau->addRow({"Report", "Pour les rapports", "Rapports techniques"});
    
    Section chapitre5("Conclusion", Section::Level::CHAPTER);
    chapitre5.addContent("Cette bibliothèque offre une solution pratique pour la génération de documents LaTeX à partir de code C++.");
    chapitre5.addContent("Les perspectives futures incluent le support d'autres types de documents et d'environnements LaTeX.");
    
    // Ajout des chapitres au rapport
    rapport.addSection(chapitre1);
    rapport.addSection(chapitre2);
    rapport.addSection(chapitre3);
    rapport.addSection(chapitre4);
    rapport.addSection(chapitre5);
    
    // Ajout des environnements
    rapport.addEnvironment(classes);
    rapport.addEnvironment(equation);
    
    // Sauvegarde du document dans un fichier
    if (rapport.saveToFile("output","exemple_rapport.tex")) {
        std::cout << "Le fichier exemple_rapport.tex a été créé avec succès." << std::endl;
    } else {
        std::cerr << "Erreur lors de la création du fichier exemple_rapport.tex" << std::endl;
    }
    
    return 0;
}