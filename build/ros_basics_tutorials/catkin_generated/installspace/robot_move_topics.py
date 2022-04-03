#!/usr/bin/env python3
import rospy 
from geometry_msgs.msg import Twist

#whatch the tutorials and continue 

def move():
    #start the node
    rospy.init_node('robot_cleaner',anonymous=True)
    velocity_publisher = rospy.Publisher('/turtle1/cmd_vel',Twist,queue_size=10)
    vel_msg = Twist()

    #receiving the user's input
    print('Lets move your robot \n')
    speed = int(input("input your speed :"))
    distance = int(input("Type your distance :"))
    isForward = int(input("Forward?: "))

    #checking if the movement is forward or backwards
    if(isForward):
        vel_msg.linear.x= speed
    else:
        vel_msg.linear.x= -speed
    #since we are moving just in x-axis
    vel_msg.linear.y=0
    vel_msg.linear.z=0
    vel_msg.angular.x=0
    vel_msg.angular.y=0
    vel_msg.angular.z=0

    while not rospy.is_shutdown():
        #setting the current time for distance calculus 
        t0 = rospy.Time.now().to_sec()
        current_distance = 0 
        #loop to move the turtle in a specified distance
        while(current_distance < distance):
            #publish the velocity 
            velocity_publisher.publish(vel_msg)
            #Takes actual time to velocity calculus 
            t1 = rospy.Time.now().to_sec()
            #calculate distancePoseStamp
            current_distance = speed*(t1-t0)
        #after the loop , stop the robot
        vel_msg.linear.x= 0 
        #force the robot stop
        velocity_publisher.publish(vel_msg)

if __name__ == '__main__':
    try:
        move()
    except rospy.ROSInterruptException :pass

