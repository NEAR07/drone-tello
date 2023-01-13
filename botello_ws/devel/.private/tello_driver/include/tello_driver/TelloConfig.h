//#line 2 "/opt/ros/melodic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"
// *********************************************************
//
// File autogenerated for the tello_driver package
// by the dynamic_reconfigure package.
// Please do not edit.
//
// ********************************************************/

#ifndef __tello_driver__TELLOCONFIG_H__
#define __tello_driver__TELLOCONFIG_H__

#if __cplusplus >= 201103L
#define DYNAMIC_RECONFIGURE_FINAL final
#else
#define DYNAMIC_RECONFIGURE_FINAL
#endif

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <ros/node_handle.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/config_init_mutex.h>
#include <boost/any.hpp>

namespace tello_driver
{
  class TelloConfigStatics;

  class TelloConfig
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l,
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }

      virtual void clamp(TelloConfig &config, const TelloConfig &max, const TelloConfig &min) const = 0;
      virtual void calcLevel(uint32_t &level, const TelloConfig &config1, const TelloConfig &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, TelloConfig &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const TelloConfig &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, TelloConfig &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const TelloConfig &config) const = 0;
      virtual void getValue(const TelloConfig &config, boost::any &val) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;

    // Final keyword added to class because it has virtual methods and inherits
    // from a class with a non-virtual destructor.
    template <class T>
    class ParamDescription DYNAMIC_RECONFIGURE_FINAL : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string a_name, std::string a_type, uint32_t a_level,
          std::string a_description, std::string a_edit_method, T TelloConfig::* a_f) :
        AbstractParamDescription(a_name, a_type, a_level, a_description, a_edit_method),
        field(a_f)
      {}

      T TelloConfig::* field;

      virtual void clamp(TelloConfig &config, const TelloConfig &max, const TelloConfig &min) const
      {
        if (config.*field > max.*field)
          config.*field = max.*field;

        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const TelloConfig &config1, const TelloConfig &config2) const
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, TelloConfig &config) const
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const TelloConfig &config) const
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, TelloConfig &config) const
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const TelloConfig &config) const
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }

      virtual void getValue(const TelloConfig &config, boost::any &val) const
      {
        val = config.*field;
      }
    };

    class AbstractGroupDescription : public dynamic_reconfigure::Group
    {
      public:
      AbstractGroupDescription(std::string n, std::string t, int p, int i, bool s)
      {
        name = n;
        type = t;
        parent = p;
        state = s;
        id = i;
      }

      std::vector<AbstractParamDescriptionConstPtr> abstract_parameters;
      bool state;

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &config) const =0;
      virtual void updateParams(boost::any &cfg, TelloConfig &top) const= 0;
      virtual void setInitialState(boost::any &cfg) const = 0;


      void convertParams()
      {
        for(std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = abstract_parameters.begin(); i != abstract_parameters.end(); ++i)
        {
          parameters.push_back(dynamic_reconfigure::ParamDescription(**i));
        }
      }
    };

    typedef boost::shared_ptr<AbstractGroupDescription> AbstractGroupDescriptionPtr;
    typedef boost::shared_ptr<const AbstractGroupDescription> AbstractGroupDescriptionConstPtr;

    // Final keyword added to class because it has virtual methods and inherits
    // from a class with a non-virtual destructor.
    template<class T, class PT>
    class GroupDescription DYNAMIC_RECONFIGURE_FINAL : public AbstractGroupDescription
    {
    public:
      GroupDescription(std::string a_name, std::string a_type, int a_parent, int a_id, bool a_s, T PT::* a_f) : AbstractGroupDescription(a_name, a_type, a_parent, a_id, a_s), field(a_f)
      {
      }

      GroupDescription(const GroupDescription<T, PT>& g): AbstractGroupDescription(g.name, g.type, g.parent, g.id, g.state), field(g.field), groups(g.groups)
      {
        parameters = g.parameters;
        abstract_parameters = g.abstract_parameters;
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        if(!dynamic_reconfigure::ConfigTools::getGroupState(msg, name, (*config).*field))
          return false;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          if(!(*i)->fromMessage(msg, n))
            return false;
        }

        return true;
      }

      virtual void setInitialState(boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        T* group = &((*config).*field);
        group->state = state;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = boost::any(&((*config).*field));
          (*i)->setInitialState(n);
        }

      }

      virtual void updateParams(boost::any &cfg, TelloConfig &top) const
      {
        PT* config = boost::any_cast<PT*>(cfg);

        T* f = &((*config).*field);
        f->setParams(top, abstract_parameters);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          (*i)->updateParams(n, top);
        }
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &cfg) const
      {
        const PT config = boost::any_cast<PT>(cfg);
        dynamic_reconfigure::ConfigTools::appendGroup<T>(msg, name, id, parent, config.*field);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          (*i)->toMessage(msg, config.*field);
        }
      }

      T PT::* field;
      std::vector<TelloConfig::AbstractGroupDescriptionConstPtr> groups;
    };

class DEFAULT
{
  public:
    DEFAULT()
    {
      state = true;
      name = "Default";
    }

    void setParams(TelloConfig &config, const std::vector<AbstractParamDescriptionConstPtr> params)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator _i = params.begin(); _i != params.end(); ++_i)
      {
        boost::any val;
        (*_i)->getValue(config, val);

        if("fixed_video_rate"==(*_i)->name){fixed_video_rate = boost::any_cast<int>(val);}
        if("video_req_sps_hz"==(*_i)->name){video_req_sps_hz = boost::any_cast<double>(val);}
        if("altitude_limit"==(*_i)->name){altitude_limit = boost::any_cast<int>(val);}
        if("attitude_limit"==(*_i)->name){attitude_limit = boost::any_cast<int>(val);}
        if("low_bat_threshold"==(*_i)->name){low_bat_threshold = boost::any_cast<int>(val);}
        if("vel_cmd_scale"==(*_i)->name){vel_cmd_scale = boost::any_cast<double>(val);}
      }
    }

    int fixed_video_rate;
double video_req_sps_hz;
int altitude_limit;
int attitude_limit;
int low_bat_threshold;
double vel_cmd_scale;

    bool state;
    std::string name;

    
}groups;



//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int fixed_video_rate;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double video_req_sps_hz;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int altitude_limit;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int attitude_limit;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int low_bat_threshold;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double vel_cmd_scale;
//#line 228 "/opt/ros/melodic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();

      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        if ((*i)->fromMessage(msg, *this))
          count++;

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i ++)
      {
        if ((*i)->id == 0)
        {
          boost::any n = boost::any(this);
          (*i)->updateParams(n, *this);
          (*i)->fromMessage(msg, n);
        }
      }

      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("TelloConfig::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    // This version of __toMessage__ is used during initialization of
    // statics when __getParamDescriptions__ can't be called yet.
    void __toMessage__(dynamic_reconfigure::Config &msg, const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__, const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toMessage(msg, *this);

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        if((*i)->id == 0)
        {
          (*i)->toMessage(msg, *this);
        }
      }
    }

    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      __toMessage__(msg, __param_descriptions__, __group_descriptions__);
    }

    void __toServer__(const ros::NodeHandle &nh) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      static bool setup=false;

      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->fromServer(nh, *this);

      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++){
        if (!setup && (*i)->id == 0) {
          setup = true;
          boost::any n = boost::any(this);
          (*i)->setInitialState(n);
        }
      }
    }

    void __clamp__()
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const TelloConfig &__max__ = __getMax__();
      const TelloConfig &__min__ = __getMin__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const TelloConfig &config) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->calcLevel(level, config, *this);
      return level;
    }

    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__();
    static const TelloConfig &__getDefault__();
    static const TelloConfig &__getMax__();
    static const TelloConfig &__getMin__();
    static const std::vector<AbstractParamDescriptionConstPtr> &__getParamDescriptions__();
    static const std::vector<AbstractGroupDescriptionConstPtr> &__getGroupDescriptions__();

  private:
    static const TelloConfigStatics *__get_statics__();
  };

  template <> // Max and min are ignored for strings.
  inline void TelloConfig::ParamDescription<std::string>::clamp(TelloConfig &config, const TelloConfig &max, const TelloConfig &min) const
  {
    (void) config;
    (void) min;
    (void) max;
    return;
  }

  class TelloConfigStatics
  {
    friend class TelloConfig;

    TelloConfigStatics()
    {
TelloConfig::GroupDescription<TelloConfig::DEFAULT, TelloConfig> Default("Default", "", 0, 0, true, &TelloConfig::groups);
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.fixed_video_rate = 0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.fixed_video_rate = 4;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.fixed_video_rate = 0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<int>("fixed_video_rate", "int", 0, "Video rate", "{'enum_description': 'Video rate options', 'enum': [{'srcline': 9, 'description': 'Let drone automatically decide', 'srcfile': '/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg', 'cconsttype': 'const int', 'value': 0, 'ctype': 'int', 'type': 'int', 'name': 'Auto'}, {'srcline': 10, 'description': 'Set to 1.0Mb/s fixed rate (~4.5KB/frame @ 30fps)', 'srcfile': '/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg', 'cconsttype': 'const int', 'value': 1, 'ctype': 'int', 'type': 'int', 'name': '1p0Mbps'}, {'srcline': 11, 'description': 'Set to 1.5Mb/s fixed rate (~6.6KB/frame @ 30fps)', 'srcfile': '/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg', 'cconsttype': 'const int', 'value': 2, 'ctype': 'int', 'type': 'int', 'name': '1p5Mbps'}, {'srcline': 12, 'description': 'Set to 2.0Mb/s fixed rate (~8.5KB/frame @ 30fps)', 'srcfile': '/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg', 'cconsttype': 'const int', 'value': 3, 'ctype': 'int', 'type': 'int', 'name': '2p0Mbps'}, {'srcline': 13, 'description': 'Set to 2.5Mb/s fixed rate ( ~11KB/frame @ 30fps)', 'srcfile': '/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg', 'cconsttype': 'const int', 'value': 4, 'ctype': 'int', 'type': 'int', 'name': '2p5Mbps'}]}", &TelloConfig::fixed_video_rate)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<int>("fixed_video_rate", "int", 0, "Video rate", "{'enum_description': 'Video rate options', 'enum': [{'srcline': 9, 'description': 'Let drone automatically decide', 'srcfile': '/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg', 'cconsttype': 'const int', 'value': 0, 'ctype': 'int', 'type': 'int', 'name': 'Auto'}, {'srcline': 10, 'description': 'Set to 1.0Mb/s fixed rate (~4.5KB/frame @ 30fps)', 'srcfile': '/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg', 'cconsttype': 'const int', 'value': 1, 'ctype': 'int', 'type': 'int', 'name': '1p0Mbps'}, {'srcline': 11, 'description': 'Set to 1.5Mb/s fixed rate (~6.6KB/frame @ 30fps)', 'srcfile': '/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg', 'cconsttype': 'const int', 'value': 2, 'ctype': 'int', 'type': 'int', 'name': '1p5Mbps'}, {'srcline': 12, 'description': 'Set to 2.0Mb/s fixed rate (~8.5KB/frame @ 30fps)', 'srcfile': '/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg', 'cconsttype': 'const int', 'value': 3, 'ctype': 'int', 'type': 'int', 'name': '2p0Mbps'}, {'srcline': 13, 'description': 'Set to 2.5Mb/s fixed rate ( ~11KB/frame @ 30fps)', 'srcfile': '/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg', 'cconsttype': 'const int', 'value': 4, 'ctype': 'int', 'type': 'int', 'name': '2p5Mbps'}]}", &TelloConfig::fixed_video_rate)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.video_req_sps_hz = 0.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.video_req_sps_hz = 4.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.video_req_sps_hz = 0.5;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<double>("video_req_sps_hz", "double", 0, "Rate for regularly requesting SPS data from drone (0: disabled)", "", &TelloConfig::video_req_sps_hz)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<double>("video_req_sps_hz", "double", 0, "Rate for regularly requesting SPS data from drone (0: disabled)", "", &TelloConfig::video_req_sps_hz)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.altitude_limit = 1;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.altitude_limit = 100;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.altitude_limit = 10;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<int>("altitude_limit", "int", 0, "Limit altitude of Tello", "", &TelloConfig::altitude_limit)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<int>("altitude_limit", "int", 0, "Limit altitude of Tello", "", &TelloConfig::altitude_limit)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.attitude_limit = 15;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.attitude_limit = 25;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.attitude_limit = 15;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<int>("attitude_limit", "int", 0, "Limit attitude of Tello", "", &TelloConfig::attitude_limit)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<int>("attitude_limit", "int", 0, "Limit attitude of Tello", "", &TelloConfig::attitude_limit)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.low_bat_threshold = 1;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.low_bat_threshold = 100;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.low_bat_threshold = 7;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<int>("low_bat_threshold", "int", 0, "Set low battery threshold of Tello", "", &TelloConfig::low_bat_threshold)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<int>("low_bat_threshold", "int", 0, "Set low battery threshold of Tello", "", &TelloConfig::low_bat_threshold)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.vel_cmd_scale = 0.01;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.vel_cmd_scale = 1.0;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.vel_cmd_scale = 0.5;
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<double>("vel_cmd_scale", "double", 0, "Scale (down) vel_cmd value", "", &TelloConfig::vel_cmd_scale)));
//#line 291 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(TelloConfig::AbstractParamDescriptionConstPtr(new TelloConfig::ParamDescription<double>("vel_cmd_scale", "double", 0, "Scale (down) vel_cmd value", "", &TelloConfig::vel_cmd_scale)));
//#line 246 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.convertParams();
//#line 246 "/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __group_descriptions__.push_back(TelloConfig::AbstractGroupDescriptionConstPtr(new TelloConfig::GroupDescription<TelloConfig::DEFAULT, TelloConfig>(Default)));
//#line 366 "/opt/ros/melodic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

      for (std::vector<TelloConfig::AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        __description_message__.groups.push_back(**i);
      }
      __max__.__toMessage__(__description_message__.max, __param_descriptions__, __group_descriptions__);
      __min__.__toMessage__(__description_message__.min, __param_descriptions__, __group_descriptions__);
      __default__.__toMessage__(__description_message__.dflt, __param_descriptions__, __group_descriptions__);
    }
    std::vector<TelloConfig::AbstractParamDescriptionConstPtr> __param_descriptions__;
    std::vector<TelloConfig::AbstractGroupDescriptionConstPtr> __group_descriptions__;
    TelloConfig __max__;
    TelloConfig __min__;
    TelloConfig __default__;
    dynamic_reconfigure::ConfigDescription __description_message__;

    static const TelloConfigStatics *get_instance()
    {
      // Split this off in a separate function because I know that
      // instance will get initialized the first time get_instance is
      // called, and I am guaranteeing that get_instance gets called at
      // most once.
      static TelloConfigStatics instance;
      return &instance;
    }
  };

  inline const dynamic_reconfigure::ConfigDescription &TelloConfig::__getDescriptionMessage__()
  {
    return __get_statics__()->__description_message__;
  }

  inline const TelloConfig &TelloConfig::__getDefault__()
  {
    return __get_statics__()->__default__;
  }

  inline const TelloConfig &TelloConfig::__getMax__()
  {
    return __get_statics__()->__max__;
  }

  inline const TelloConfig &TelloConfig::__getMin__()
  {
    return __get_statics__()->__min__;
  }

  inline const std::vector<TelloConfig::AbstractParamDescriptionConstPtr> &TelloConfig::__getParamDescriptions__()
  {
    return __get_statics__()->__param_descriptions__;
  }

  inline const std::vector<TelloConfig::AbstractGroupDescriptionConstPtr> &TelloConfig::__getGroupDescriptions__()
  {
    return __get_statics__()->__group_descriptions__;
  }

  inline const TelloConfigStatics *TelloConfig::__get_statics__()
  {
    const static TelloConfigStatics *statics;

    if (statics) // Common case
      return statics;

    boost::mutex::scoped_lock lock(dynamic_reconfigure::__init_mutex__);

    if (statics) // In case we lost a race.
      return statics;

    statics = TelloConfigStatics::get_instance();

    return statics;
  }

//#line 9 "/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg"
      const int Tello_Auto = 0;
//#line 10 "/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg"
      const int Tello_1p0Mbps = 1;
//#line 11 "/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg"
      const int Tello_1p5Mbps = 2;
//#line 12 "/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg"
      const int Tello_2p0Mbps = 3;
//#line 13 "/home/nizhar/botello/botello_ws/src/tello_driver/cfg/Tello.cfg"
      const int Tello_2p5Mbps = 4;
}

#undef DYNAMIC_RECONFIGURE_FINAL

#endif // __TELLORECONFIGURATOR_H__
