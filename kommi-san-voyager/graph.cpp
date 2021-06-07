#include "graph.h"
#include "newedgeform.h"
#include "deledgeform.h"
#include "ui_graph.h"
#include <cmath>
#include <QTextStream>

QTextStream cout(stdout);
QTextStream cin(stdin);

int     radiusA = 30,
        radiusB = 170;


QString Graph::komm()
{
    int n;
    int* res;
    int** help;
    int*** mat;

    n = Vnumber;

    help = new int* [n];

    res = new int[n];

    mat = new int** [n];

    for (int i = 0; i <= n; i++)
    {
        help[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        mat[i] = new int* [n];
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 0) {
                mat[i][j] = nullptr;
                continue;
            }
            mat[i][j] = new int(matrix[i][j]);
        }
    }

    for (int l = 0; l < n; l++)
    {
        for (int i = 0; i < n; i++)
        {
            int min = 1000000;
            for (int j = 0; j < n; j++)
                if (mat[i][j] && min > * mat[i][j])
                    min = *mat[i][j];
            for (int j = 0; j < n; j++)
                if (mat[i][j])
                    *mat[i][j] -= min;
        }
        for (int j = 0; j < n; j++)
        {
            int min = 1000000;
            for (int i = 0; i < n; i++)
                if (mat[i][j] && min > * mat[i][j])
                    min = *mat[i][j];
            for (int i = 0; i < n; i++)
                if (mat[i][j])
                    *mat[i][j] -= min;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                help[i][j] = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] && !*mat[i][j])
                {
                    int hmin = 1000000;
                    int vmin = 1000000;

                    for (int l = 0; l < n; l++)
                        if (l != i && mat[l][j] && hmin > * mat[l][j])
                            hmin = *mat[l][j];

                    for (int l = 0; l < n; l++)
                        if (l != j && mat[i][l] && vmin > * mat[i][l])
                            vmin = *mat[i][l];

                    help[i][j] = hmin + vmin;
                }
            }

        int mcost = 0, mi = 0, mj = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (mat[i][j] && mcost < help[i][j])
                {
                    mcost = help[i][j];
                    mi = i;
                    mj = j;
                }
        res[mi] = mj;

        for (int i = 0; i < n; i++)
            mat[i][mj] = nullptr;

        for (int i = 0; i < n; i++)
            mat[mi][i] = nullptr;

        mat[mj][mi] = nullptr;
    }

    int s = 0;
    QString tmp = "";

    for (int i = 0, j = 0; i < n; i++)
    {
        j = res[i];
        s += matrix[i][j];
    }
    cout << "\n";
    tmp += QString("\nНаилучший путь: ");
    int temp = 0;
    for (int l = 0; l < n;)
    {
        for (int i = 0, j = 0; i < n; i++)
        {
            if (temp == 0 || i + 1 == temp)
            {
                if (temp == 0) tmp += QString::number(i + 1);
                j = res[i];
                temp = j + 1;
                if (temp > 0)	tmp += QString(" -> ") + QString::number(temp);
                l++;
            }
        }
    }
    tmp += QString("\nДрузей встретилось: ") + QString::number(s);
    return tmp;
}

int Graph::getFriends(const int vertex1, const int vertex2)
{
    if (vertex1 >= 0 && vertex1 < matrix.size() && vertex2 >=0 && vertex2 < matrix.size())
        return matrix[vertex1][vertex2];
    else
        return 0;
}

void Graph::DrawLines(QGraphicsScene* scene)
{
    int     centerX= scene->width() / 2,
            centerY = scene->height() / 2;
    double iter = 2 * 3.1415 / matrix.size();
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            if (getFriends(i, j) > 0){
                int     vertex1_x = centerX + cos(iter * i) * radiusB,
                        vertex1_y = centerY - sin(iter * i) * radiusB,
                        vertex2_x = centerX + cos(iter * j) * radiusB,
                        vertex2_y = centerY - sin(iter * j) * radiusB;
                QGraphicsItem *line = scene->addLine(vertex1_x, vertex1_y, vertex2_x, vertex2_y);
                scene->addItem(line);
                QGraphicsTextItem *number = scene->addText(QString::number(getFriends(i, j)), QFont("Times"));
                number->setPos((vertex2_x + vertex1_x) / 2, (vertex2_y + vertex1_y) / 2);
            }
        }
    }
}

void Graph::DrawNodes(QGraphicsScene* scene)
{
    int     centerX= scene->width() / 2,
            centerY = scene->height() / 2;
    double iter = 2 * 3.1415 / matrix.size();
    for (int i = 0; i < matrix.size(); i++){
        QGraphicsItem *node = scene->addEllipse(centerX + cos(iter * i) * radiusB - radiusA,
                                                centerY - sin(iter * i) * radiusB - radiusA, 2*radiusA, 2*radiusA,
                                                QPen(Qt::black), QBrush(Qt::white));
        scene->addItem(node);
        QGraphicsTextItem *number = scene->addText(QString::number(i+1), QFont("Times"));
        number->setPos(centerX + cos(iter * i) * radiusB - radiusA + 12,
                       centerY - sin(iter * i) * radiusB - radiusA + 6);
    }
}


void Graph::DrawGraph(QGraphicsScene* scene)
{
    DrawLines(scene);
    DrawNodes(scene);
}

void Graph::Draw()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 400, 400);

    ui->graphicsView->setScene(scene);
    scene->clear();
    DrawGraph(scene);
}



void Graph::DelWay(int src, int trg)
{
    matrix[src - 1][trg - 1] = 0;
}

void Graph::addWay(int source, int target, int weight)
{
    if (source > 0 && source <= Vnumber && target > 0 && target <= Vnumber && weight > 0)
    {
        matrix[source - 1][target - 1] = weight;
    } else cout << "Ошибка добавления ребра!!!";
}

void Graph::newWay()
{
    NewEdgeForm window;
    window.setModal(true);
    window.max_Vnumber = Vnumber + 1;
    window.exec();
    if(window.isSaved)
    {
        int source = window.source;
        int target = window.target;
        int weight = window.weight;

        addWay(source, target, weight);
        addWay(target, source, weight);
    }
}

Graph::Graph(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Graph)
{

    ui->setupUi(this);
    this->setWindowTitle("Kommi-san-voyager");
    setWindowIcon(QIcon(":/pics/icon"));
    Vnumber = 6;
    matrix = { {0, 12, 0, 0, 0, 16 },
               {12, 0, 24, 0, 23, 0 },
               {0, 24, 0, 5, 6, 0 },
               {0, 0, 5, 0, 0, 6 },
               {0, 23, 6, 0, 0, 8 },
               {16, 0, 0, 6, 8, 0 } };
    window()->setWindowFlags(window()->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    Draw();

}

Graph::~Graph()
{
    delete ui;
}

void Graph::on_b_komi_clicked()
{
    ui->result->setText(komm());
}

void Graph::on_b_addEdge_clicked()
{
    newWay();
    Draw();
}

void Graph::on_b_delEdge_clicked()
{
    DelEdgeForm window;
    window.setModal(true);
    window.max_Vnumber = Vnumber + 1;
    window.exec();
    if (window.isSaved)
    {
        int source = window.source;
        int target = window.target;
        DelWay(source, target);
        DelWay(target, source);
        Draw();
    }
}
