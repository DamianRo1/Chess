#include <iostream>
#include <stdlib.h>
class Piezas
{
public:
    Piezas(char Color) : mColor(Color) {}
    ~Piezas() {}
    virtual char GetPieza() = 0;
    char GetColor() {
        return mColor;
    }
    bool EsLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, Piezas* Tablero[8][8]) {
        Piezas* qpDest = Tablero[iDestRow][iDestCol];
        if ((qpDest == 0) || (mColor != qpDest->GetColor())) {
            return CuadLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, Tablero);
        }
        return false;
    }
private:
    virtual bool CuadLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, Piezas* Tablero[8][8]) = 0;
    char mColor;
};

class Pn : public Piezas
{
public:
    Pn(char Color) : Piezas(Color) {}
    ~Pn() {}
private:
    virtual char GetPieza() {
        return 'P';
    }
    bool CuadLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, Piezas* Tablero[8][8]) {
        Piezas* qpDest = Tablero[iDestRow][iDestCol];
        if (qpDest == 0) {
            if (iSrcCol == iDestCol) {
                if (GetColor() == '#') {
                    if (iDestRow == iSrcRow + 1) {
                        return true;
                    }
                } else {
                    if (iDestRow == iSrcRow - 1) {
                        return true;
                    }
                }
            }
        } else {
            if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1)) {
                if (GetColor() == '#') {
                    if (iDestRow == iSrcRow + 1) {
                        return true;
                    }
                } else {
                    if (iDestRow == iSrcRow - 1) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

class Cb : public Piezas
{
public:
    Cb(char Color) : Piezas(Color) {}
    ~Cb() {}
private:
    virtual char GetPieza() {
        return 'C';
    }
    bool CuadLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, Piezas* Tablero[8][8]) {
        if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1)) {
            if ((iSrcRow == iDestRow + 2) || (iSrcRow == iDestRow - 2)) {
                return true;
            }
        }
        if ((iSrcCol == iDestCol + 2) || (iSrcCol == iDestCol - 2)) {
            if ((iSrcRow == iDestRow + 1) || (iSrcRow == iDestRow - 1)) {
                return true;
            }
        }
        return false;
    }
};

class Al : public Piezas
{
public:
    Al(char Color) : Piezas(Color) {}
    ~Al() {}
private:
    virtual char GetPieza() {
        return 'A';
    }
    bool CuadLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, Piezas* Tablero[8][8]) {
        if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            int iCheckRow;
            int iCheckCol;
            for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
                iCheckRow !=  iDestRow;
                iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
            {
                if (Tablero[iCheckRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Tr : public Piezas
{
public:
    Tr(char Color) : Piezas(Color) {}
    ~Tr() {}
private:
    virtual char GetPieza() {
        return 'T';
    }
    bool CuadLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, Piezas* Tablero[8][8]) {
        if (iSrcRow == iDestRow) {
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {
                if (Tablero[iSrcRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (iDestCol == iSrcCol) {
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {
                if (Tablero[iCheckRow][iSrcCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Qn : public Piezas
{
public:
    Qn(char Color) : Piezas(Color) {}
    ~Qn() {}
private:
    virtual char GetPieza() {
        return 'Q';
    }
    bool CuadLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, Piezas* Tablero[8][8]) {
        if (iSrcRow == iDestRow) {
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {
                if (Tablero[iSrcRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (iDestCol == iSrcCol) {
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {
                if (Tablero[iCheckRow][iSrcCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            int iCheckRow;
            int iCheckCol;
            for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
                iCheckRow !=  iDestRow;
                iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
            {
                if (Tablero[iCheckRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Ry : public Piezas
{
public:
    Ry(char Color) : Piezas(Color) {}
    ~Ry() {}
private:
    virtual char GetPieza() {
        return 'R';
    }
    bool CuadLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, Piezas* Tablero[8][8]) {
        int iRowDelta = iDestRow - iSrcRow;
        int iColDelta = iDestCol - iSrcCol;
        if (((iRowDelta >= -1) && (iRowDelta <= 1)) &&
            ((iColDelta >= -1) && (iColDelta <= 1)))
        {
            return true;
        }
        return false;
    }
};

class CTab
{
public:
    CTab() {
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                TabPrin[iRow][iCol] = 0;
            }
        }
        for (int iCol = 0; iCol < 8; ++iCol) {
            TabPrin[6][iCol] = new Pn('0');
        }
        TabPrin[7][0] = new Tr('0');
        TabPrin[7][1] = new Cb('0');
        TabPrin[7][2] = new Al('0');
        TabPrin[7][3] = new Ry('0');
        TabPrin[7][4] = new Qn('0');
        TabPrin[7][5] = new Al('0');
        TabPrin[7][6] = new Cb('0');
        TabPrin[7][7] = new Tr('0');
        for (int iCol = 0; iCol < 8; ++iCol) {
            TabPrin[1][iCol] = new Pn('#');
        }
        TabPrin[0][0] = new Tr('#');
        TabPrin[0][1] = new Cb('#');
        TabPrin[0][2] = new Al('#');
        TabPrin[0][3] = new Ry('#');
        TabPrin[0][4] = new Qn('#');
        TabPrin[0][5] = new Al('#');
        TabPrin[0][6] = new Cb('#');
        TabPrin[0][7] = new Tr('#');
    }
    ~CTab() {
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                delete TabPrin[iRow][iCol];
                TabPrin[iRow][iCol] = 0;
            }
        }
    }

    void Print() {
        using namespace std;
        const int kiSquareWidth = 4;
        const int kiSquareHeight = 3;
        for (int iRow = 0; iRow < 8*kiSquareHeight; ++iRow) {
            int iSquareRow = iRow/kiSquareHeight;
            if (iRow % 3 == 1) {
                cout << ' ' << (char)('1' + 7 - iSquareRow) << ' ';
            } else {
                cout << "---";
            }
            for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
                int iSquareCol = iCol/kiSquareWidth;
                if (((iRow % 3) == 1) && ((iCol % 4) == 1 || (iCol % 4) == 2) && TabPrin[7-iSquareRow][iSquareCol] != 0) {
                    if ((iCol % 4) == 1) {
                        cout << TabPrin[7-iSquareRow][iSquareCol]->GetColor();
                    } else {
                        cout << TabPrin[7-iSquareRow][iSquareCol]->GetPieza();
                    }
                } else {
                    if ((iSquareRow + iSquareCol) % 2 == 1) {
                        cout << '/';
                    } else {
                        cout << ' ';
                    }
                }
            }
            cout << endl;
        }
        for (int iRow = 0; iRow < kiSquareHeight; ++iRow) {
            if (iRow % 3 == 1) {
                cout << "---";
                for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
                    int iSquareCol = iCol/kiSquareWidth;
                    if ((iCol % 4) == 1) {
                        cout << (iSquareCol + 1);
                    } else {
                        cout << ' ';
                    }
                }
                cout << endl;
            } else {
                for (int iCol = 1; iCol < 9*kiSquareWidth; ++iCol) {
                    cout << ' ';
                }
                cout << endl;
            }
        }
    }

    bool EnJaque(char Color) {
        int iKingRow;
        int iKingCol;
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (TabPrin[iRow][iCol] != 0) {
                    if (TabPrin[iRow][iCol]->GetColor() == Color) {
                        if (TabPrin[iRow][iCol]->GetPieza() == 'K') {
                            iKingRow = iRow;
                            iKingCol = iCol;
                        }
                    }
                }
            }
        }
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (TabPrin[iRow][iCol] != 0) {
                    if (TabPrin[iRow][iCol]->GetColor() != Color) {
                        if (TabPrin[iRow][iCol]->EsLegal(iRow, iCol, iKingRow, iKingCol, TabPrin)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool CanMove(char Color) {
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (TabPrin[iRow][iCol] != 0) {
                    if (TabPrin[iRow][iCol]->GetColor() == Color) {
                        for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow) {
                            for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol) {
                                if (TabPrin[iRow][iCol]->EsLegal(iRow, iCol, iMoveRow, iMoveCol, TabPrin)) {
                                    Piezas* qpTemp                   = TabPrin[iMoveRow][iMoveCol];
                                    TabPrin[iMoveRow][iMoveCol]   = TabPrin[iRow][iCol];
                                    TabPrin[iRow][iCol]           = 0;
                                    bool bCanMove = !EnJaque(Color);
                                    TabPrin[iRow][iCol]           = TabPrin[iMoveRow][iMoveCol];
                                    TabPrin[iMoveRow][iMoveCol]   = qpTemp;
                                    if (bCanMove) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    Piezas* TabPrin[8][8];
};

class ATab
{
public:
    ATab() : mcTJ('#') {}
    ~ATab() {}

    void Start() {
        do {
            GetNextMove(mqTab.TabPrin);
            Turno();
        } while (!Fin());
        mqTab.Print();
    }

    void GetNextMove(Piezas* Tablero[8][8]) {
        using namespace std;
        bool bMoVal     = false;
        do {
            system ("clear");
            cout<<"Ajedrez "<<endl;
            mqTab.Print();

            cout << "Turno de "<< mcTJ << ": ";
            int iStartMove;
            cin >> iStartMove;
            int iStartRow = (iStartMove / 10) - 1;
            int iStartCol = (iStartMove % 10) - 1;

            cout << "a: ";
            int iEndMove;
            cin >> iEndMove;
            int iEndRow = (iEndMove / 10) - 1;
            int iEndCol = (iEndMove % 10) - 1;

            if ((iStartRow >= 0 && iStartRow <= 7) &&
                (iStartCol >= 0 && iStartCol <= 7) &&
                (iEndRow >= 0 && iEndRow <= 7) &&
                (iEndCol >= 0 && iEndCol <= 7)) {
                Piezas* qpPiezActu = Tablero[iStartRow][iStartCol];
                if ((qpPiezActu != 0) && (qpPiezActu->GetColor() == mcTJ)) {
                    if (qpPiezActu->EsLegal(iStartRow, iStartCol, iEndRow, iEndCol, Tablero)) {
                        Piezas* qpTemp                   = Tablero[iEndRow][iEndCol];
                        Tablero[iEndRow][iEndCol]     = Tablero[iStartRow][iStartCol];
                        Tablero[iStartRow][iStartCol] = 0;
                        if (!mqTab.EnJaque(mcTJ)) {
                            delete qpTemp;
                            bMoVal = true;
                        } else {
                            Tablero[iStartRow][iStartCol] = Tablero[iEndRow][iEndCol];
                            Tablero[iEndRow][iEndCol]     = qpTemp;
                        }
                    }
                }
            }
            if (!bMoVal) {
                cout << "Invalido" << endl;
            }
        } while (!bMoVal);
    }

    void Turno() {
        mcTJ = (mcTJ == '#') ? '0' : '#';
    }

    bool Fin() {
        bool bCanMove(false);
        bCanMove = mqTab.CanMove(mcTJ);
        if (!bCanMove) {
            if (mqTab.EnJaque(mcTJ)) {
                Turno();
                std::cout << "Jaque mate, " << mcTJ << " Gana" << std::endl;
            } else {
                std::cout << "empate" << std::endl;
            }
        }
        return !bCanMove;
    }
private:
    CTab mqTab;
    char mcTJ;
};

int main() {
    ATab qGame;
    qGame.Start();
    return 0;
}
