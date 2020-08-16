#ifndef SIMROBCOMM_H
#define SIMROBCOMM_H

//#include <math.h>
#include <QtNetwork/QUdpSocket>
#include "robot/robot_proxy.h"
#include "robot/navigation/drives/omni_drive.h"
#include "utilities/point.h"

#define _USE_MATH_DEFINES
#include <math.h>


class RobotLowLevelControls;

/*! @brief RobComm to send to the grSim simulator
 * @details uses ProtoBuf and QT to send to a computer running a grSim simulator */

class ProxyGrsim : public RobotProxy
{
    Q_OBJECT
public:
    //! @brief Constructor sets the IP and port to send to **see .cpp**
    ProxyGrsim(YAML::Node* t_node);

    void sendVels(const QSet<Robot*>&) override;

    bool hasKicker() override;
    bool isHolonomic() override;
    Pilot* createPilot(Robot* robot) override;

    QString getName() override;

private:
    OmniDrive drive;
    QUdpSocket* udpsocket = new QUdpSocket(this);
    QHostAddress _addr;
    quint16 _port;

    //! @brief Sends a standard packet to the simulator
    void sendPacket(Robot *robot);

    //! @brief Sends all replacement packets to the simulator
    void sendReplacementPackets();


    void getWheelSpeeds(Point velocity, float angular_speed, double wheelSpeeds[4]);

protected:
    void close() override;
};

#endif // SIMROBCOMM_H