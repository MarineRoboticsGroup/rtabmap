# FROM mitmrg/gtsam-opencv-pcl:latest
# Possibly useful unsure
FROM ros:melodic-perception

# ENV GIT_SSH_COMMAND 'ssh -i ~/.ssh/id_rsa -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no'
# ARG USER_ID
# RUN adduser --uid $USER_ID mrg --disabled-password --gecos="mrg"
# RUN usermod -aG sudo mrg
# RUN echo "mrg ALL=NOPASSWD: ALL" >> /etc/sudoers
# USER mrg
# WORKDIR /home/mrg


USER root

# Install build dependencies
RUN apt-get update && \
    apt-get install -y ros-melodic-rtabmap ros-melodic-rtabmap-ros && \
    apt-get remove -y ros-melodic-rtabmap ros-melodic-rtabmap-ros

# g2o from source
RUN apt-get remove -y ros-melodic-libg2o && \
    git clone https://github.com/RainerKuemmerle/g2o.git && \
    cd g2o && \
    mkdir build && cd build && \
    cmake -DBUILD_WITH_MARCH_NATIVE=OFF -DG2O_BUILD_APPS=OFF -DG2O_BUILD_EXAMPLES=OFF -DG2O_USE_OPENGL=OFF .. && \
    make -j4 && \
    make install

# GTSAM
RUN cd ~ && \
    git clone --branch 4.0.0 https://github.com/borglab/gtsam.git && \
    cd ~/gtsam/ && \
    mkdir build && \
    cd build && \
    cmake -DGTSAM_USE_SYSTEM_EIGEN=ON -DGTSAM_BUILD_WITH_MARCH_NATIVE=OFF -DGTSAM_BUILD_UNSTABLE=ON .. && \
    make check -j4 && \
    make install -j4
