#include "ihm.h"
#include "ui_ihm.h"
#include "nouvelleruche.h"
#include "reglageruche.h"
#include <QMessageBox>
#include <QDebug>

/**
 * @file    Ihm.cpp
 * @brief   Déclaration de la classe Ihm
 * @author  ACKERMANN Théo
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe Ihm
 * @fn Ihm::Ihm
 * @param parent
 */
Ihm::Ihm(QWidget *parent) :QMainWindow(parent),ui(new Ui::ihm),ihmNouvelleRuche(0),ihmReglageRuche(0)
{
    ui->setupUi(this);

    chargerIconesBoutons();

    ihmNouvelleRuche = new IHMNouvelleRuche(this);
    ihmReglageRuche = new IHMReglageRuche(this);

    ui->comboBox_liste_ruches->addItem("Nom de la ruche");

    ui->comboBox_reglages_graphiques->addItem("1j");
    ui->comboBox_reglages_graphiques->addItem("7j");

    connect(ui->comboBox_reglages_graphiques, SIGNAL(currentIndexChanged(int)), SLOT(changerAbscisseGraphiques()));

    demarrerGraphiques();
    demarrerGraphiquesBatons();
    demarrerTableauAlertes();
}

/**
 * @brief Destructeur de la classe Ihm
 * @fn Ihm::~Ihm
 */
Ihm::~Ihm()
{
    delete ihmNouvelleRuche;
    delete ihmReglageRuche;
    delete ui;
}

/**
 * @brief Bouton/icone qui permet d'aller sur l'onglet de la ruche
 * @fn Ihm::on_pushButton_ruches_clicked
 */
void Ihm::on_pushButton_ruches_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_ACCUEIL);
    ui->pushButton_ruches->setIcon(QIcon(":/ruches.png"));

    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
}

/**
 * @brief
 *
 */
void Ihm::on_pushButton_mesures_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_MESURES);

    ui->pushButton_ruches->setIcon(QIcon(":/ruches_gris.png"));
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
}

/**
 * @brief
 *
 */
void Ihm::on_pushButton_tableaux_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_TABLEAUX);

    ui->pushButton_ruches->setIcon(QIcon(":/ruches_gris.png"));
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
}

/**
 * @brief Bouton/icone qui permet d'aller sur l'onglet des graphiques
 *
 */
void Ihm::on_pushButton_graphiques_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_GRAPHIQUES);
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques.png"));

    ui->pushButton_ruches->setIcon(QIcon(":/ruches_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
}

/**
 * @brief Bouton/icone qui permet d'aller sur l'onglet des alertes
 *
 */
void Ihm::on_pushButton_alertes_clicked()
{
    ui->stackedWidget->setCurrentIndex(PagesIHM::PAGE_ALERTES);
    ui->pushButton_alertes->setIcon(QIcon(":/alertes.png"));

    ui->pushButton_ruches->setIcon(QIcon(":/ruches_gris.png"));
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
}

/**
 * @brief Bouton qui permet d'ouvrir la fenêtre de création du nouvelle ruche
 *
 */
void Ihm::on_pushButton_nouvelle_ruche_clicked()
{
    ihmNouvelleRuche->exec();
}

/**
 * @brief Bouton qui permet d'ouvrir la fenêtre des réglages de la ruche
 *
 */
void Ihm::on_pushButton_reglage_clicked()
{
    ihmReglageRuche->exec();
}

/**
 * @brief Bouton qui permet de supprimer la ruche selectionné
 *
 */
void Ihm::on_pushButton_supprimer_ruche_clicked()
{
    QMessageBox::StandardButton reponse;
    reponse = QMessageBox::question(this,"","Êtes-vous sûr de vouloir supprimer la ruche ?",QMessageBox::Yes|QMessageBox::No); // Ajouter nom de la ruche

    if(reponse == QMessageBox::Yes)
    {
        qDebug() << Q_FUNC_INFO << "reponse : Oui";
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "reponse : Non";
    }
}

/**
 * @brief Méthode qui initialise les graphiques
 * @fn Ihm::demarrerGraphiques
 */
void Ihm::demarrerGraphiques()
{
    graphiqueTemperature();
    graphiqueHumidite();
    graphiqueLuminosite();
    //graphiquePression();
    //graphiquePoids();
    //graphiqueActivite();
}

/**
 * @brief Méthode qui initialise le graphique de température
 * @fn Ihm::graphiqueTemperature
 */
void Ihm::graphiqueTemperature()
{
    QLineSeries *temperatureInterieure = new QLineSeries();
    temperatureInterieure->setName("Intérieure");
    // Valeurs de test
    temperatureInterieure->append(0, 27);
    temperatureInterieure->append(1, 26);
    temperatureInterieure->append(2, 28);
    temperatureInterieure->append(3, 31);
    temperatureInterieure->append(4, 24);

    QLineSeries *temperatureExterieure = new QLineSeries();
    temperatureExterieure->setName("Extérieure");
    // Valeurs de test
    temperatureExterieure->append(0, 35);
    temperatureExterieure->append(1, 37);
    temperatureExterieure->append(2, 35);
    temperatureExterieure->append(3, 34);
    temperatureExterieure->append(4, 31);

    QChart *chart = new QChart();
    chart->legend()->show();
    chart->addSeries(temperatureInterieure);
    chart->addSeries(temperatureExterieure);

    chart->createDefaultAxes();
    chart->setTitle("Températures");
    ui->chartView_temperature->setChart(chart);
    ui->chartView_temperature->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd.MM");
    axisX->setTitleText("Jours");
    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("°C");
    axisY->setMin(-10);
    axisY->setMax(45);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);
}

/**
 * @brief Méthode qui initialise le graphique d'humidité
 * @fn Ihm::graphiqueHumidite
 */
void Ihm::graphiqueHumidite()
{
    QLineSeries *humidite = new QLineSeries();
    // Valeurs de test
    humidite->append(0, 27);
    humidite->append(1, 26);
    humidite->append(2, 28);
    humidite->append(3, 31);
    humidite->append(4, 24);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(humidite);
    chart->setTitle("Humidité");
    ui->chartView_humidite->setChart(chart);
    ui->chartView_humidite->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd.MM");
    axisX->setTitleText("Jours");
    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("%");
    axisY->setMin(0);
    axisY->setMax(100);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);
    //humidite->attachAxis(axisX);
}

void Ihm::graphiqueLuminosite()
{
    QLineSeries *luminosite = new QLineSeries();
    // Valeurs de test
    luminosite->append(0, 321);
    luminosite->append(1, 354);
    luminosite->append(2, 396);
    luminosite->append(3, 348);
    luminosite->append(4, 240);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(luminosite);
    chart->setTitle("Luminosité");
    ui->chartView_luminosite->setChart(chart);
    ui->chartView_luminosite->setRenderHint(QPainter::Antialiasing);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd.MM");
    axisX->setTitleText("Jours");
    axisX->setMin(QDateTime::currentDateTime().addDays(-3));
    axisX->setMax(QDateTime::currentDateTime().addDays(3));

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("lux");
    axisY->setMin(0);
    axisY->setMax(500);

    chart->setAxisY(axisY);
    chart->setAxisX(axisX);
    //luminosite->attachAxis(axisX);
}

void Ihm::changerAbscisseGraphiques()
{
    switch(ui->comboBox_reglages_graphiques->currentIndex())
    {
        case 0:
            qDebug() << Q_FUNC_INFO << "reponse : 1j";
            break;
        case 1:
            qDebug() << Q_FUNC_INFO << "reponse : 7j";
            break;
        default:
            qDebug() << Q_FUNC_INFO << ui->comboBox_reglages_graphiques->currentIndex();
     }
}

/**
 * @brief Méthode qui permet de mettre une valeur dans un graphique
 * @param serie
 * @param x
 * @param y
 */
void Ihm::setValeurGraphique(QLineSeries *serie, int x, int y)
{
    serie->append(x,y);
}

/**
 * @brief
 *
 */
void Ihm::demarrerGraphiquesBatons()
{
    graphiqueBatonTemperatureInterieure();
    graphiqueBatonTemperatureExterieure();
}

/**
 * @brief
 *
 */
void Ihm::graphiqueBatonTemperatureInterieure()
{
    QBarSet *set0 = new QBarSet("Température Intérieure");
    *set0 << 37;

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(36,40);
    axisY->setTickCount(10);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    ui->chartView_baton_temperature_interieure->setChart(chart);
}

/**
 * @brief
 *
 */
void Ihm::graphiqueBatonTemperatureExterieure()
{
    QBarSet *set0 = new QBarSet("Température Extérieure");
    *set0 << 37;

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,45);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    ui->chartView_baton_temperature_exterieure->setChart(chart);
}

/**
 * @brief
 *
 */
void Ihm::demarrerTableauAlertes()
{

}

void Ihm::chargerIconesBoutons()
{
    ui->pushButton_ruches->setIcon(QIcon(":/ruches.png"));
    ui->pushButton_graphiques->setIcon(QIcon(":/graphiques_gris.png"));
    ui->pushButton_alertes->setIcon(QIcon(":/alertes_gris.png"));
}
