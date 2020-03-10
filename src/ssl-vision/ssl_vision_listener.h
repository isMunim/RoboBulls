#ifndef VISIONCOMM_H
#define VISIONCOMM_H
#include <string>
#include <QtCore/QThread>
#include "model/game_state.h"
#include "robot/robot.h"
#include "my_kalman_filter.h"
#include "gui/guiinterface.h"
#include "yaml-cpp/yaml.h"

#include <QUdpSocket>
#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include "messages_robocup_ssl_refbox_log.pb.h"
#include<atomic>



//! @brief Sets the minimum confidence to consider a ball reading as valid
//#if SIMULATED
//const float CONF_THRESHOLD_BALL = 0.9;
//#else
const float CONF_THRESHOLD_BALL = 0.8;//CNM
//#endif

//! @brief Sets the minimum confidence to consider a robot as a valid reading
const float CONF_THRESHOLD_BOTS = 0.90;

/**
 * @brief The VisionComm class recieves information from the vision cameras
 * @author Origin. Narges Ghaedi, JamesW
 * @details Detects the robots and ball and puts each robot in the corresponding team
 * based on robot's color (Blue team/ Yellow team)
 */
class SSLVisionListener: public QThread
{
public:
    SSLVisionListener( YAML::Node comm_node);

    void run() override;
    void stop();

private:
    std::atomic_bool done;
    int vision_port = 0;
    std::string vision_addr = "";

protected:


    //! @brief Parses an SSL_DetectionFrame and fills out GameModel
    void recieveRobotTeam(const SSL_DetectionFrame& frame, int whichTeam);

    //! @brief Parses an SSL_DetectionFrame and fills out GameModel
    void recieveBall(const SSL_DetectionFrame& frame);

    //! @brief Updates GameModel information to fill out a robot
    void receiveRobot(const SSL_DetectionRobot& robot, int detectedTeamColor);


    //! @brief Returns true if we are using four or two cameras.
    bool isFourCameraMode();

    SSL_WrapperPacket packet;       //! Packet recieved by client
    SSL_DetectionFrame frames[4];   //! Accumulates frames
    bool frames_state[4]{false};    //! Marks whether frames are dirty or clean
    int resetFrames = 0;            //! Frames passed up remove all potential robot detections
    int totalframes = 0;            //! Total frames passed since start
    int rob_readings[2][MAX_ROBOTS]={{0}};  //! Number of detections of each blue robot
    bool FOUR_CAMERA_MODE = false;    //! Are we in four-camera mode (true)? Or Two-camera mode?

    MyKalmanFilter kfilter = MyKalmanFilter();                //! Kalman filter instance


};

#endif // VISIONCOMM_H


