#include "latexgen.h"
#include <iostream>
#include <memory>

using namespace LatexGen;

int main()
{
    std::cout << "Démonstration de la génération de documents LaTeX multilingues\n"
              << std::endl;

    // Exemple en français
    std::cout << "Création d'un article en français..." << std::endl;
    Article articleFrancais("Mon Article Scientifique", "Jean Dupont", "\\today", Language::FRENCH);
    articleFrancais.setAbstract("Ceci est un résumé de l'article qui présente brièvement le contenu et les principaux résultats.");

    // Ajout de paquets supplémentaires pour le français
    articleFrancais.addPackage("babel", "french");
    articleFrancais.addPackage("listings");

    Section introFr("Introduction", Section::Level::SECTION);
    introFr.addContent("Dans cette section, nous présentons le contexte de notre travail sur la génération de documents LaTeX multilingues.");
    introFr.addContent("Les objectifs de cette étude sont les suivants :");

    auto objectifsFr = std::make_shared<List>(List::ListType::ENUMERATE);
    objectifsFr->addItem("Développer une bibliothèque C++ pour la génération de documents LaTeX");
    objectifsFr->addItem("Ajouter le support multilingue à la bibliothèque");
    objectifsFr->addItem("Démontrer l'utilisation avec différentes langues");

    Section conclusionFr("Conclusion", Section::Level::SECTION);
    conclusionFr.addContent("Nous avons démontré la possibilité de générer des documents LaTeX en français.");

    articleFrancais.addSection(introFr);
    articleFrancais.addEnvironment(objectifsFr);
    articleFrancais.addSection(conclusionFr);

    if (articleFrancais.saveToFile("output", "exemple_article_fr.tex"))
    {
        std::cout << "Le fichier exemple_article_fr.tex a été créé avec succès." << std::endl;
    }

    // Exemple en allemand
    std::cout << "\nCréation d'un article en allemand..." << std::endl;
    Article articleAllemand("Mein Wissenschaftlicher Artikel", "Hans Schmidt", "\\today", Language::GERMAN);
    articleAllemand.setAbstract("Dies ist eine Zusammenfassung des Artikels, der kurz den Inhalt und die wichtigsten Ergebnisse vorstellt.");

    Section introDE("Einleitung", Section::Level::SECTION);
    introDE.addContent("In diesem Abschnitt stellen wir den Kontext unserer Arbeit zur Generierung mehrsprachiger LaTeX-Dokumente vor.");

    auto objectifsDE = std::make_shared<List>(List::ListType::ENUMERATE);
    objectifsDE->addItem("Entwicklung einer C++-Bibliothek zur Generierung von LaTeX-Dokumenten");
    objectifsDE->addItem("Hinzufügen von mehrsprachiger Unterstützung zur Bibliothek");

    Section conclusionDE("Schlussfolgerung", Section::Level::SECTION);
    conclusionDE.addContent("Wir haben die Möglichkeit demonstriert, LaTeX-Dokumente auf Deutsch zu generieren.");

    articleAllemand.addSection(introDE);
    articleAllemand.addEnvironment(objectifsDE);
    articleAllemand.addSection(conclusionDE);

    if (articleAllemand.saveToFile("output","beispiel_artikel_de.tex"))
    {
        std::cout << "Le fichier beispiel_artikel_de.tex a été créé avec succès." << std::endl;
    }

    // Exemple de rapport en espagnol
    std::cout << "\nCréation d'un rapport en espagnol..." << std::endl;
    Report reporteEspanol("Mi Informe Técnico", "Carlos Rodriguez", "\\today", Language::SPANISH);
    reporteEspanol.setAbstract("Este informe presenta los resultados de un estudio técnico sobre la generación de documentos LaTeX multilingües.");
    reporteEspanol.includeTableOfContents(true);

    Section capituloES("Introducción", Section::Level::CHAPTER);
    capituloES.addContent("Este informe presenta una biblioteca C++ para la generación de documentos LaTeX en varios idiomas.");

    Section metodologiaES("Metodología", Section::Level::CHAPTER);
    metodologiaES.addContent("Nuestra metodología se basa en el uso de la biblioteca Babel y otros paquetes para el soporte multilingüe.");

    Section seccionES("Implementación", Section::Level::SECTION);
    seccionES.addContent("La implementación utiliza una enumeración de idiomas y configuraciones específicas para cada idioma.");
    metodologiaES.addContent(seccionES.generate());

    Section conclusionES("Conclusión", Section::Level::CHAPTER);
    conclusionES.addContent("Hemos demostrado la capacidad de generar documentos LaTeX en español.");

    reporteEspanol.addSection(capituloES);
    reporteEspanol.addSection(metodologiaES);
    reporteEspanol.addSection(conclusionES);

    if (reporteEspanol.saveToFile("output","ejemplo_informe_es.tex"))
    {
        std::cout << "Le fichier ejemplo_informe_es.tex a été créé avec succès." << std::endl;
    }

    // Exemple multilingue (document principal en anglais avec sections en différentes langues)
    std::cout << "\nCréation d'un document multilingue..." << std::endl;
    Report reportMultilingue("Multilingual LaTeX Document Generation", "International Team", "\\today", Language::ENGLISH);
    reportMultilingue.setAbstract("This report demonstrates the ability to generate LaTeX documents with multilingual content.");
    reportMultilingue.includeTableOfContents(true);

    // Ajouter des packages pour toutes les langues que nous allons utiliser
    reportMultilingue.addPackage("babel", "english,french,german=ngerman,provide=*,spanish,provide=*,italian,provide=*");

    Section introMulti("Introduction", Section::Level::CHAPTER);
    introMulti.addContent("This project demonstrates a C++ library for generating LaTeX documents with multilingual support.");

    Section frenchSection("Section en Français", Section::Level::CHAPTER);
    frenchSection.addContent("\\begin{otherlanguage}{french}\n");
    frenchSection.addContent("Cette section est écrite en français. La bibliothèque LatexGenCpp permet de générer des documents LaTeX multilingues.");
    frenchSection.addContent("Nous pouvons facilement switcher entre différentes langues dans le même document.");
    frenchSection.addContent("\\end{otherlanguage}\n");

    Section germanSection("Deutsche Sektion", Section::Level::CHAPTER);
    germanSection.addContent("\\begin{otherlanguage*}{german}\n"); // Utiliser otherlanguage* et 'german' au lieu de 'ngerman'
    germanSection.addContent("Dieser Abschnitt ist auf Deutsch geschrieben. Die LatexGenCpp-Bibliothek ermöglicht die Erstellung mehrsprachiger LaTeX-Dokumente.");
    germanSection.addContent("Wir können in demselben Dokument einfach zwischen verschiedenen Sprachen wechseln.");
    germanSection.addContent("\\end{otherlanguage*}\n");

    Section spanishSection("Sección en Español", Section::Level::CHAPTER);
    spanishSection.addContent("\\begin{otherlanguage*}{spanish}\n"); // Utiliser otherlanguage*
    spanishSection.addContent("Esta sección está escrita en español. La biblioteca LatexGenCpp permite generar documentos LaTeX multilingües.");
    spanishSection.addContent("Podemos cambiar fácilmente entre diferentes idiomas en el mismo documento.");
    spanishSection.addContent("\\end{otherlanguage*}\n");

    Section conclusionMulti("Conclusion", Section::Level::CHAPTER);
    conclusionMulti.addContent("We have demonstrated the ability to create multilingual LaTeX documents with our C++ library.");

    reportMultilingue.addSection(introMulti);
    reportMultilingue.addSection(frenchSection);
    reportMultilingue.addSection(germanSection);
    reportMultilingue.addSection(spanishSection);
    reportMultilingue.addSection(conclusionMulti);

    if (reportMultilingue.saveToFile("output","multilingual_report.tex"))
    {
        std::cout << "Le fichier multilingual_report.tex a été créé avec succès." << std::endl;
    }

    return 0;
}