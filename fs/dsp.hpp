#ifndef __DSP_hpp__
#define __DSP_hpp__

#include <map>
#include <string>
#include <cstring>
#include <iostream>

#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/UI.h>

namespace mydsp {

class EasyUI : public UI {
public:
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {};
    virtual void openTabBox(const char* label) {}
    virtual void openHorizontalBox(const char* name) {}
    virtual void openVerticalBox(const char* name) {}
    virtual void declare(FAUSTFLOAT* entry, const char* key, const char* value) {}

    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {
        set_parameter(label, zone);
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {
        set_parameter(label, zone);
    }
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {
        set_parameter(label, zone);
    }
    virtual void addVerticalSlider(const char* name, FAUSTFLOAT* entry, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
        set_parameter(name, entry);
    }
    virtual void addHorizontalSlider(const char* name, FAUSTFLOAT* entry, FAUSTFLOAT defvalue, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
        set_parameter(name, entry);
    }
    virtual void addButton(const char* name, FAUSTFLOAT* entry) {
        set_parameter(name, entry);
    }
    virtual void addNumEntry(const char* name, FAUSTFLOAT* entry, FAUSTFLOAT defvalue, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
        set_parameter(name, entry);
    }

    virtual void closeBox() {}

    FAUSTFLOAT* value(const char* key) {
        if ( map_.find(key) == map_.end() ) {
            std::cerr << "Can't find target key in UI" << std::endl;
            abort();
        }

        return map_[key];
    }

    FAUSTFLOAT* value(const size_t i) {
        if ( i >= values_.size() ) {
            std::cerr << "Can't find target value in UI" << std::endl;
            abort();
        }
        return values_[i];
    }

    size_t numValues() {
        return values_.size();
    }

private:
    struct keycomp {
        bool operator() (const char* lhs, const char* rhs) const {
            return std::strcmp(lhs, rhs) < 0;
        }
    };

    void set_parameter(const char* name, FAUSTFLOAT* target) {
        map_[name] = target;
        values_.push_back(target);
    }

    std::map<const char* , FAUSTFLOAT*, keycomp> map_;
    std::vector<FAUSTFLOAT*> values_;
};

}
#endif
