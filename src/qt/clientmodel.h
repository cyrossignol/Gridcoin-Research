#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QObject>

#include <atomic>

class OptionsModel;
class AddressTableModel;
class TransactionTableModel;
class BanTableModel;
class PeerTableModel;

class ConvergedScraperStats;
class CWallet;

QT_BEGIN_NAMESPACE
class QDateTime;
class QTimer;
QT_END_NAMESPACE

/** Model for Bitcoin network client. */
class ClientModel : public QObject
{
    Q_OBJECT
public:
    explicit ClientModel(OptionsModel *optionsModel, QObject *parent = 0);
    ~ClientModel();

    OptionsModel *getOptionsModel();
    PeerTableModel *getPeerTableModel();
    BanTableModel *getBanTableModel();

    int getNumConnections() const;
    int getNumBlocks() const;
	quint64 getTotalBytesRecv() const;
    quint64 getTotalBytesSent() const;


    QDateTime getLastBlockDate() const;

    //! Return true if client connected to testnet
    bool isTestNet() const;
    //! Return true if core is doing initial block download
    bool inInitialBlockDownload() const;
    //! Return conservative estimate of total number of blocks, or 0 if unknown
    int getNumBlocksOfPeers() const;
    //! Return the difficulty of the block at the chain tip.
    double getDifficulty() const;
    //! Return estimated network staking weight from the average of recent blocks.
    double getNetWeight() const;
    //! Return warnings to be displayed in status bar
    QString getStatusBarWarnings() const;
    //! Get miner and staking status warnings
    QString getMinerWarnings() const;

    QString formatFullVersion() const;
    QString formatBuildDate() const;
    QString clientName() const;
    QString formatClientStartupTime() const;

    QString formatBoostVersion()  const;
    const ConvergedScraperStats& getConvergedScraperStatsCache() const;
private:
    OptionsModel *optionsModel;
    PeerTableModel *peerTableModel;
    BanTableModel *banTableModel;

    QTimer *pollTimer;

    void subscribeToCoreSignals();
    void unsubscribeFromCoreSignals();
signals:
    void numConnectionsChanged(int count);
    void numBlocksChanged(int count, int countOfPeers);
    void difficultyChanged(double difficulty);
	void bytesChanged(quint64 totalBytesIn, quint64 totalBytesOut);
    void minerStatusChanged(bool staking, double netWeight, double coinWeight, double etts_days);
    void updateScraperLog(QString message);
    void updateScraperStatus(int ScraperEventtype, int status);

    //! Asynchronous error notification
    void error(const QString &title, const QString &message, bool modal);

public slots:
    void updateNumBlocks(int height, int64_t best_time);
    void updateTimer();
    void updateBanlist();
    void updateNumConnections(int numConnections);
    void updateAlert(const QString &hash, int status);
    void updateMinerStatus(bool staking, double coin_weight);
    void updateScraper(int scraperEventtype, int status, const QString message);
};

#endif // CLIENTMODEL_H
