#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/nizhar/catkin_ws/src/tello_driver"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/nizhar/catkin_ws/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/nizhar/catkin_ws/install/lib/python2.7/dist-packages:/home/nizhar/catkin_ws/build/tello_driver/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/nizhar/catkin_ws/build/tello_driver" \
    "/usr/bin/python2" \
    "/home/nizhar/catkin_ws/src/tello_driver/setup.py" \
     \
    build --build-base "/home/nizhar/catkin_ws/build/tello_driver" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/nizhar/catkin_ws/install" --install-scripts="/home/nizhar/catkin_ws/install/bin"
