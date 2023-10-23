#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <filesystem>

struct Asset
{
protected:
  virtual bool load(const std::filesystem::path& _sPath) = 0;
};

class AssetManager
{
public:
  AssetManager(const AssetManager&) = delete;
  void operator=(const AssetManager&) = delete;

  static AssetManager& GetInstance()
  {
    static AssetManager instance;
    return instance;
  }

  template <class TAssetType>
  std::shared_ptr<TAssetType> loadAsset(const std::filesystem::path& _sPath)
  {
    std::shared_ptr<TAssetType> pAsset = std::make_shared<TAssetType>();
    if (pAsset->load(_sPath))
    {
      std::string sPath = _sPath.string();
      m_dctAssetDictionary[sPath] = pAsset;
      return pAsset;
    }

    return nullptr;
  }
  
  template <class TAssetType>
  std::shared_ptr<TAssetType> getAsset(const std::string& _sId) const
  {
    auto itElement = m_dctAssetDictionary.find(_sId);
    if (itElement != m_dctAssetDictionary.end())
    {
      return std::make_shared<TAssetType>(itElement->second);
    }

    return nullptr;
  }

private:
  AssetManager();
  ~AssetManager();

  std::unordered_map<std::string, std::shared_ptr<Asset>> m_dctAssetDictionary;
};