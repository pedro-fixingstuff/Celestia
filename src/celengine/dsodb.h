//
// C++ Interface: dsodb
//
// Description:
//
//
// Author: Toti <root@totibox>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#pragma once

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <celcompat/filesystem.h>
#include <celengine/dsooctree.h>
#include <celengine/name.h>

constexpr inline unsigned int MAX_DSO_NAMES = 10;

// 100 Gly - on the order of the current size of the universe
constexpr inline float DSO_OCTREE_ROOT_SIZE = 1.0e11f;

//NOTE: this one and starDatabase should be derived from a common base class since they share lots of code and functionality.
class DSODatabase
{
 public:
    DSODatabase() = default;
    ~DSODatabase() = default;

    DeepSkyObject* getDSO(const std::uint32_t) const;
    std::uint32_t size() const;

    DeepSkyObject* find(const AstroCatalog::IndexNumber catalogNumber) const;
    DeepSkyObject* find(std::string_view, bool i18n) const;

    void getCompletion(std::vector<std::string>&, std::string_view) const;

    void findVisibleDSOs(DSOHandler& dsoHandler,
                         const Eigen::Vector3d& obsPosition,
                         const Eigen::Quaternionf& obsOrientation,
                         float fovY,
                         float aspectRatio,
                         float limitingMag) const;

    void findCloseDSOs(DSOHandler& dsoHandler,
                       const Eigen::Vector3d& obsPosition,
                       float radius) const;

    std::string getDSOName    (const DeepSkyObject*, bool i18n = false) const;
    std::string getDSONameList(const DeepSkyObject*, const unsigned int maxNames = MAX_DSO_NAMES) const;

    NameDatabase* getNameDatabase() const;
    void setNameDatabase(std::unique_ptr<NameDatabase>&&);

    bool load(std::istream&, const fs::path& resourcePath = fs::path());
    void finish();

    float getAverageAbsoluteMagnitude() const;

private:
    void buildIndexes();
    void buildOctree();
    void calcAvgAbsMag();

    std::vector<std::unique_ptr<DeepSkyObject>> DSOs;
    std::unique_ptr<NameDatabase> namesDB;
    std::vector<std::uint32_t> catalogNumberIndex;
    std::unique_ptr<DSOOctree> octreeRoot;
    AstroCatalog::IndexNumber nextAutoCatalogNumber{ 0xfffffffe };

    float avgAbsMag{ 0.0f };
};

inline DeepSkyObject*
DSODatabase::getDSO(const std::uint32_t n) const
{
    return DSOs[n].get();
}

inline std::uint32_t
DSODatabase::size() const
{
    return static_cast<std::uint32_t>(DSOs.size());
}
