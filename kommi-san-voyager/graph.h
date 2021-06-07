#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QString>
#include <QGraphicsTextItem>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class Graph; }
QT_END_NAMESPACE


class Graph : public QMainWindow
{
    Q_OBJECT

private:
    Ui::Graph *ui;
    QGraphicsScene *scene;

public:
    int Vnumber;
    std::vector<std::vector<int>> matrix;

    Graph(QWidget *parent = nullptr);
    ~Graph();
    int getFriends(const int vertex1, const int vertex2);
    void DrawLines(QGraphicsScene* scene);
    void DrawNodes(QGraphicsScene* scene);
    void DrawGraph(QGraphicsScene* scene);

    void newWay();
    void addWay(int source, int target, int weight);
    void DelWay(int src, int trg);
    void Draw();
    QString komm();
private slots:
    void on_b_komi_clicked();
    void on_b_addEdge_clicked();
    void on_b_delEdge_clicked();
};
#endif // GRAPH_H
