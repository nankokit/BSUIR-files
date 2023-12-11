#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"
class Bishop : public ChessPiece
{
public:
  Bishop(QString team, QGraphicsItem *parent = 0);
  void setImage();

  void moves();
};

#endif // BISHOP_H
#include "bishop.h"
#include <QDebug>
#include "game.h"
extern Game *game;

Bishop::Bishop(QString team, QGraphicsItem *parent) : ChessPiece(team, parent)
{
  setImage();
}

void Bishop::setImage()
{
  if (side == "WHITE")
    setPixmap(QPixmap("E:/kursovaya3sem/myProject/media/whitebishop.png"));
  else
    setPixmap(QPixmap("E:/kursovaya3sem/myProject/media/blackbishop.png"));
}

void Bishop::moves()
{
  location.clear();
  int row = this->getCurrentBox()->rowLoc;
  int col = this->getCurrentBox()->colLoc;
  QString team = this->getSide();
  // For upper Left

  for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
  {
    if (game->collection[i][j]->getChessPieceColor() == team)
    {
      break;
    }
    else
    {
      location.append(game->collection[i][j]);
      if (boxSetting(location.last()))
      {
        break;
      }
    }
  }

  // For upper right

  for (int i = row - 1, j = col + 1; i >= 0 && j <= 7; i--, j++)
  {
    if (game->collection[i][j]->getChessPieceColor() == team)
    {
      break;
    }
    else
    {
      location.append(game->collection[i][j]);
      if (boxSetting(location.last()))
      {
        break;
      }
    }
  }

  // For downward right

  for (int i = row + 1, j = col + 1; i <= 7 && j <= 7; i++, j++)
  {
    if (game->collection[i][j]->getChessPieceColor() == team)
    {
      break;
    }
    else
    {
      location.append(game->collection[i][j]);
      if (boxSetting(location.last()))
      {
        break;
      }
    }
  }

  // For downward left

  for (int i = row + 1, j = col - 1; i <= 7 && j >= 0; i++, j--)
  {
    if (game->collection[i][j]->getChessPieceColor() == team)
    {
      break;
    }
    else
    {
      location.append(game->collection[i][j]);
      if (boxSetting(location.last()))
      {
        break;
      }
    }
  }
}
#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

class Button : public QObject, public QGraphicsRectItem
{
  Q_OBJECT
public:
  Button(QString name, QGraphicsItem *parent = NULL);

  // public methods
  void setFont(QFont const textFont);

  // events
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
  void clicked();

private:
  QGraphicsTextItem *text;
};
#endif // BUTTON_H
#include "button.h"
#include "qfont.h"
#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(QString name, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
  // draw the rect
  setRect(0, 0, 150, 50);
  QBrush brush;
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(QColor::fromRgb(qRgb(61, 61, 61)));
  setBrush(brush);

  // draw Text
  text = new QGraphicsTextItem(name, this);
  int xPos = rect().width() / 2 - text->boundingRect().width() / 2 - 15;
  int yPos = rect().height() / 2 - text->boundingRect().height() / 2;
  text->setPos(xPos, yPos);
  text->setDefaultTextColor(QColor::fromRgb(qRgb(247, 247, 247)));

  // Allow responding to hover
  setAcceptHoverEvents(true);
}

void Button::setFont(QFont const textFont)
{
  text->setFont(textFont);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event)
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  // change color
  if (event)
  {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgb(qRgb(127, 127, 127)));
    setBrush(brush);
  }
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  // change color
  if (event)
  {
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgb(qRgb(61, 61, 61)));
    setBrush(brush);
  }
}
#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include "chesspiece.h"
class ChessBoard
{
public:
  ChessBoard();

  // drawing public function
  void drawBoxes(int x, int y);
  void addChessPiece();

  void setUpWhite();
  void setUpBlack();
  void reset();

private:
  QList<ChessPiece *> white;
  QList<ChessPiece *> black;
};

#endif // CHESSBOARD_H

#include "chessboard.h"
#include "chessbox.h"
#include "game.h"
#include "queen.h"
#include "rook.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"

extern Game *game;

ChessBoard::ChessBoard()
{
  setUpBlack();
  setUpWhite();
}

void ChessBoard::drawBoxes(int x, int y)
{
  int SHIFT = 100;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      ChessBox *box = new ChessBox();
      game->collection[i][j] = box;
      box->rowLoc = i;
      box->colLoc = j;
      box->setPos(x + SHIFT * j, y + SHIFT * i);
      if ((i + j) % 2 == 0)
        box->setOriginalColor(QColor::fromRgb(qRgb(247, 247, 247))); // white
      else
        box->setOriginalColor(QColor::fromRgb(qRgb(118, 118, 118))); // black
      game->addToScene(box);
    }
  }
}

void ChessBoard::addChessPiece()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      ChessBox *box = game->collection[i][j];
      if (i < 2)
      {
        static int k;
        box->placePiece(black[k]);
        game->alivePiece.append(black[k]);
        game->addToScene(black[k++]);
      }
      if (i > 5)
      {
        static int h;
        box->placePiece(white[h]);
        game->alivePiece.append(white[h]);
        game->addToScene(white[h++]);
      }
    }
  }
}

void ChessBoard::setUpWhite()
{
  ChessPiece *piece;
  for (int i = 0; i < 8; i++)
  {
    piece = new Pawn("WHITE");
    white.append(piece);
  }
  piece = new Rook("WHITE");
  white.append(piece);
  piece = new Knight("WHITE");
  white.append(piece);
  piece = new Bishop("WHITE");
  white.append(piece);
  piece = new Queen("WHITE");
  white.append(piece);
  piece = new King("WHITE");
  white.append(piece);
  piece = new Bishop("WHITE");
  white.append(piece);
  piece = new Knight("WHITE");
  white.append(piece);
  piece = new Rook("WHITE");
  white.append(piece);
}

void ChessBoard::setUpBlack()
{
  ChessPiece *piece;
  piece = new Rook("BLACK");
  black.append(piece);
  piece = new Knight("BLACK");
  black.append(piece);
  piece = new Bishop("BLACK");
  black.append(piece);
  piece = new Queen("BLACK");
  black.append(piece);
  piece = new King("BLACK");
  black.append(piece);
  piece = new Bishop("BLACK");
  black.append(piece);
  piece = new Knight("BLACK");
  black.append(piece);
  piece = new Rook("BLACK");
  black.append(piece);
  for (int i = 0; i < 8; i++)
  {
    piece = new Pawn("BLACK");
    black.append(piece);
  }
}

void ChessBoard::reset()
{
  int k = 0;
  int h = 0;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      ChessBox *box = game->collection[i][j];
      box->setHasChessPiece(false);
      box->setChessPieceColor("NONE");
      box->currentPiece = NULL;
      if (i < 2)
      {
        box->placePiece(black[k]);
        black[k]->setIsPlaced(true);
        black[k]->firstMove = true;
        game->alivePiece.append(black[k++]);
      }
      if (i > 5)
      {
        box->placePiece(white[h]);
        white[h]->setIsPlaced(true);
        white[h]->firstMove = true;
        game->alivePiece.append(white[h++]);
      }
    }
  }
}
#include "chessbox.h"
#include "game.h"
#include <QDebug>
#include "king.h"

extern Game *game;

ChessBox::ChessBox(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
  // making the Square CHess Box
  setRect(0, 0, 100, 100);
  brush.setStyle(Qt::SolidPattern);
  setZValue(-1);
  setHasChessPiece(false);
  setChessPieceColor("NONE");
  currentPiece = NULL;
}

ChessBox::~ChessBox()
{
  delete this;
}

void ChessBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  // Deselecting counter part of ChessPiece
  if (currentPiece == game->pieceToMove && currentPiece)
  {
    currentPiece->mousePressEvent(event);
    return;
  }

  // if selected
  if (game->pieceToMove)
  {
    // if same team
    if (this->getChessPieceColor() == game->pieceToMove->getSide())
      return;
    // removing the eaten piece
    QList<ChessBox *> movLoc = game->pieceToMove->moveLocation();
    // TO make sure the selected box is in move zone
    int check = 0;
    for (size_t i = 0, n = movLoc.size(); i < n; i++)
    {
      if (movLoc[i] == this)
      {
        check++;
      }
    }
    // if not prsent return
    if (check == 0)
      return;
    // change the color back to normal
    game->pieceToMove->decolor();
    // make the first move false applicable for pawn only
    game->pieceToMove->firstMove = false;
    // this is to eat or consume the enemy present inn the movable region
    if (this->getHasChessPiece())
    {
      this->currentPiece->setIsPlaced(false);
      this->currentPiece->setCurrentBox(NULL);
      game->placeInDeadPlace(this->currentPiece);
    }
    // changing the new stat and resetting the previous left region
    game->pieceToMove->getCurrentBox()->setHasChessPiece(false);
    game->pieceToMove->getCurrentBox()->currentPiece = NULL;
    game->pieceToMove->getCurrentBox()->resetOriginalColor();
    placePiece(game->pieceToMove);

    game->pieceToMove = NULL;
    // changing turn
    game->changeTurn();
    checkForCheck();
  }
  // Selecting couterpart of the chessPiece
  else if (this->getHasChessPiece())
  {
    this->currentPiece->mousePressEvent(event);
  }
}

void ChessBox::setColor(QColor color)
{
  brush.setColor(color);
  setBrush(color);
}

void ChessBox::placePiece(ChessPiece *piece)
{
  piece->setPos(x() + 50 - piece->pixmap().width() / 2, y() + 50 - piece->pixmap().width() / 2);
  piece->setCurrentBox(this);
  setHasChessPiece(true, piece);
  currentPiece = piece;
}

void ChessBox::resetOriginalColor()
{
  setColor(originalColor);
}

void ChessBox::setOriginalColor(QColor value)
{
  originalColor = value;
  setColor(originalColor);
}

bool ChessBox::getHasChessPiece()
{
  return hasChessPiece;
}

void ChessBox::setHasChessPiece(bool value, ChessPiece *piece)
{
  hasChessPiece = value;
  if (value)
    setChessPieceColor(piece->getSide());
  else
    setChessPieceColor("NONE");
}

void ChessBox::checkForCheck()
{
  int c = 0;
  QList<ChessPiece *> pList = game->alivePiece;
  for (size_t i = 0, n = pList.size(); i < n; i++)
  {

    King *p = dynamic_cast<King *>(pList[i]);
    if (p)
    {
      continue;
    }
    pList[i]->moves();
    pList[i]->decolor();
    QList<ChessBox *> bList = pList[i]->moveLocation();
    for (size_t j = 0, n = bList.size(); j < n; j++)
    {
      King *p = dynamic_cast<King *>(bList[j]->currentPiece);
      if (p)
      {
        if (p->getSide() == pList[i]->getSide())
          continue;
        bList[j]->setColor(Qt::darkMagenta);

        //                if(pList[i]->getCurrentBox()->getChessPieceColor() == "WHITE")
        //                    emit game->whiteWon();
        //                else
        //                   emit  game->blackWon();
        //                game->gameOver();
        // pList[i]->getCurrentBox()->setColor(Qt::darkYellow);
        if (!game->check->isVisible())
          game->check->setVisible(true);
        else
        {
          bList[j]->resetOriginalColor();
          pList[i]->getCurrentBox()->resetOriginalColor();
          // game->gameOver();
        }
        c++;
      }
    }
  }
  if (!c)
  {
    game->check->setVisible(false);
    for (size_t i = 0, n = pList.size(); i < n; i++)
      pList[i]->getCurrentBox()->resetOriginalColor();
  }
}

QString ChessBox::getChessPieceColor()
{
  return chessPieceColor;
}

void ChessBox::setChessPieceColor(QString value)
{
  chessPieceColor = value;
}
