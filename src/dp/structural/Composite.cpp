// Composite is a structural design pattern
// that lets you compose objects into "tree structures"
// and then work with these structures as if they were individual objects.
// Appicability:
// (*)   when you have to implement a tree-like object structure.
// (**)  when you want the client code to treat both simple and complex elements
// uniformly. UML: docs/uml/patterns_structural_composite.drawio.svg

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <utility>

namespace {
namespace problem {
class File {
 private:
  std::string name_;

 public:
  explicit File(std::string fileName) : name_{std::move(fileName)} {}
  std::string getName() const { return this->name_; }

  void setName(const std::string& name) { this->name_ = name; }

  void open() const { std::cout << "Open file: " << name_ << "\n"; }
};

// [P1] Have the NewTypeFile => Update Folder (fields, functions)

class Folder {
 private:
  std::string name_;
  std::list<File*>
      files_;  // Should store the pointer to the actual file so when we delete
               // the file it should delete in the list
  std::list<Folder*> subFolders_;
  // [P2] What about the parrent ?

 public:
  explicit Folder(std::string name) : name_{std::move(name)} {}

  ~Folder() {
    for (File* f : files_) {
      delete f;
    }

    for (Folder* sf : subFolders_) {
      delete sf;
    }
  }

  void removeFile(const File* file) {
    files_.remove_if([file](const File* f) { return f == file; });
  }

  void removeFileByName(const std::string& name) {

    // for (auto i = _files.begin(); i != _files.end(); ++i)
    // {
    //     if ((*i)->getName() == name)
    //     {
    //         delete (*i);
    //         _files.erase(i);
    //         return;
    //     }
    // }

    auto it =
        std::find_if(files_.begin(), files_.end(),
                     [&name](const File* f) { return f->getName() == name; });

    if (it != files_.end()) {
      delete *it;        // free the memory
      files_.erase(it);  // remove the pointer from the list
    }
  }

  void removeFolderByName(const std::string& name) {
    // for (auto i = _subFolders.begin(); i != _subFolders.end(); ++i)
    // {
    //     if ((*i)->getName() == name)
    //     {
    //         delete (*i);
    //         _subFolders.erase(i);
    //         return;
    //     }
    // }
    auto it =
        std::find_if(subFolders_.begin(), subFolders_.end(),
                     [&name](const Folder* f) { return f->getName() == name; });

    if (it != subFolders_.end()) {
      delete *it;             // free the memory
      subFolders_.erase(it);  // remove the pointer from the list
    }
  }

  void addFile(File* file) { files_.push_back(file); }

  void addFolder(Folder* folder) { subFolders_.push_back(folder); }

  void removeFolder(const Folder* folder) {
    subFolders_.remove_if([folder](const Folder* f) { return f == folder; });
  }

  std::string getName() const { return name_; }

  void open() const { std::cout << "Open Folder: " << name_ << "\n"; }

  int size() const {
    int size = static_cast<int>(files_.size());

    //  Consider using std::accumulate algorithm instead of a raw loop.
    std::for_each(subFolders_.begin(), subFolders_.end(),
                  [&size](const Folder* sf) { size += sf->size(); });

    // for (const Folder *subFolder : _subFolders)
    // {
    //     size += subFolder->size();
    // }

    return size;
  }

  const std::list<Folder*>& getSubFolders() const { return subFolders_; }

  const std::list<File*>& getFiles() const { return files_; }

  void getFilesRecursive(std::list<File*>& out) const {
    out.insert(out.end(), files_.begin(), files_.end());
    for (const Folder* sf : subFolders_) {
      sf->getFilesRecursive(out);
    }
  }

  void getSubFoldersRecursive(std::list<Folder*>& out) const {
    out.insert(out.end(), subFolders_.begin(), subFolders_.end());
    for (const Folder* sf : subFolders_) {
      sf->getSubFoldersRecursive(out);
    }
  }
};

namespace client {
void clientCode(const Folder* folder) {
  std::cout << "File name: " << folder->getName() << "\n";
  folder->open();

  std::cout << "Folder size: " << folder->getName()
            << ", size: " << folder->size() << "\n";
  std::list<File*> files;
  folder->getFilesRecursive(files);
  for (const File* f : files) {
    std::cout << "\t\tFile: " << f->getName() << "\n";
  }

  std::list<Folder*> sub_folders;
  folder->getSubFoldersRecursive(sub_folders);
  for (const Folder* sf : sub_folders) {
    std::cout << "\t\tFolder: " << sf->getName() << "\n";
  }
}
}  // namespace client

void run() {
  std::cout << "\n\n";
  auto* root = new Folder("root");
  root->open();

  // Prepare files
  File* file1 = new File("fileName1.txt");
  File* file2 = new File("fileName2.txt");
  File* file3 = new File("fileName3.txt");
  root->addFile(new File(*file1));
  root->addFile(new File(*file2));
  root->addFile(new File(*file3));

  auto* sub_folder1 = new Folder("subFolder1");
  auto* sub_folder2 = new Folder("subFolder2");
  auto* sub_folder3 = new Folder("subFolder3");

  root->addFolder(new Folder(*sub_folder1));
  root->addFolder(new Folder(*sub_folder2));
  root->addFolder(new Folder(*sub_folder3));

  client::clientCode(root);

  // Clean up memory
  delete sub_folder1;
  delete sub_folder2;
  delete sub_folder3;
  delete file1;
  delete file2;
  delete file3;

  root->removeFileByName("fileName1.txt");
  client::clientCode(root);
  delete root;  // deletes all files/subfolders inside recursively
}

}  // namespace problem

namespace composite_pattern {
/**
 * Component is the abstraction for leafs and composites.
 * It defines the interface that must be implemented by the objects in the
 * composition. For example a file system resource defines move, copy, rename,
 * and getSize methods for files and folders.
 */
class FileSystem {
 private:
  FileSystem* parent_{};
  std::string name_;

 public:
  explicit FileSystem(std::string fileName) : name_{std::move(fileName)} {}
  virtual ~FileSystem() {
    std::cout << "Destructor: " << this->getName() << "\n";
  }

  FileSystem* getParent() const { return parent_; }

  void setParent(FileSystem* parent) { parent_ = parent; }

  std::string getName() const { return this->name_; }

  virtual int size() const { return 1; }

  void setName(const std::string& name) { this->name_ = name; }

  virtual void add(FileSystem*) {
    // do nothing here
  }

  virtual void remove(FileSystem*) {
    // do nothing here
  }

  /**
   * Check if the component is composite or not
   * You can provide a method that lets the client code figure out whether a
   * component can bear children.
   */
  virtual bool isComposite() const { return false; }

  virtual void open() const = 0;
};

/**
 * Composite - A Composite stores child components in addition to implementing
 * methods defined by the component interface. Composites implement methods
 * defined in the Component interface by delegating to child components. In
 * addition composites provide additional methods for adding, removing, as well
 * as getting components.
 */
class Folder : public FileSystem {
 private:
  std::list<FileSystem*> children_;

  // Remove children
  [[maybe_unused]] void removeChildren(const FileSystem* file) {
    children_.remove_if([file](const FileSystem* f) { return f == file; });
  }

  [[maybe_unused]] void removeChildrenByName(const std::string& name) {

    auto it = std::find_if(
        children_.begin(), children_.end(),
        [&name](const FileSystem* f) { return f->getName() == name; });

    if (it != children_.end()) {
      delete *it;           // free the memory
      children_.erase(it);  // remove the pointer from the list
    }
  }

  [[maybe_unused]] const std::list<FileSystem*>& getChildren() const {
    return children_;
  }

  void getChildrensRecursive(std::list<FileSystem*>& out) const {
    for (FileSystem* fs : children_) {
      if (fs->isComposite()) {
        const Folder* f = static_cast<Folder*>(fs);
        if (f != nullptr)
          f->getChildrensRecursive(out);
      } else {
        out.push_back(fs);
      }
    }
  }

 public:
  explicit Folder(const std::string& name) : FileSystem{name} {}

  ~Folder() override {
    // Delete folder should delete all children
    for (auto* f : children_) {
      std::cout << "Folder '" << this->getName()
                << "' deleted : " << f->getName() << "\n";
      delete f;
    }
  }

  void add(FileSystem* fs) override {
    std::cout << "Folder '" << this->getName() << "' added : " << fs->getName()
              << "\n";
    children_.push_back(fs);
    fs->setParent(this);
  }

  void remove(FileSystem* fs) override {
    std::cout << "Folder: " << this->getName() << "removed : " << fs->getName()
              << "\n";
    children_.remove(fs);
    fs->setParent(nullptr);
  }

  void open() const override {
    std::cout << "Open Folder: " << this->getName() << "\n";
  }

  int size() const override {
    int size = static_cast<int>(children_.size());
    std::for_each(children_.begin(), children_.end(), [&size](FileSystem* fs) {
      if (fs->isComposite()) {
        const Folder* f = static_cast<Folder*>(fs);
        if (f != nullptr)
          size += f->size();
      }
    });

    return size;
  }
};

/**
 * The Leaf class represents the end objects of a composition. A leaf can't have
 * any children.
 *
 * Usually, it's the Leaf objects that do the actual work, whereas Composite
 * objects only delegate to their sub-components.
 */
class File : public FileSystem {
 public:
  explicit File(const std::string& name) : FileSystem{name} {}

  void open() const override {
    std::cout << "Open File: " << this->getName() << "\n";
  }
};

class ZipFile : public FileSystem {
 public:
  explicit ZipFile(const std::string& name) : FileSystem{name} {}

  void open() const override {
    std::cout << "Open ZipFile: " << this->getName() << "\n";
  }
};

class ShortCut : public FileSystem {
 private:
  FileSystem* origin_;

 public:
  explicit ShortCut(FileSystem* fs) : FileSystem{fs->getName()} {
    origin_ = fs;
  }

  void open() const override {
    std::cout << "Open ShortCut: " << this->getName() << "\n";
    if (origin_ != nullptr) {
      std::cout << "Navigate to: " << origin_->getName() << "\n";
    } else {
      std::cout << "Original file no longer exist\n";
    }
  }
};

namespace client {
void clientCode(const FileSystem* fs) {
  std::cout << "File name: " << fs->getName() << ", size: " << fs->size()
            << "\n";
  fs->open();
}
}  // namespace client

void run() {
  std::cout << "\n\n";
  FileSystem* root = new Folder("root");
  root->open();

  // Prepare files
  FileSystem* file1 = new File("file_name.txt");
  FileSystem* file2 = new ZipFile("zipfile_name.txt");
  FileSystem* file3 = new ShortCut(file2);
  root->add(file1);
  root->add(file2);
  root->add(file3);
  client::clientCode(file1);
  client::clientCode(root);

  auto* sub_folder1 = new Folder("subFolder1");
  auto* sub_folder2 = new Folder("subFolder2");
  auto* sub_folder3 = new Folder("subFolder3");
  root->add(sub_folder1);
  root->add(sub_folder2);
  root->add(sub_folder3);
  client::clientCode(root);

  root->remove(file1);
  delete file1;

  root->remove(file2);
  delete file2;

  root->remove(file3);
  delete file3;

  delete root;  // deletes all files/subfolders inside recursively
}

}  // namespace composite_pattern

}  // namespace

#include "ExampleRegistry.h"

class CompositeExample : public IExample {
 public:
  std::string group() const override { return "dp/structural"; }
  std::string name() const override { return "Composite"; }
  std::string description() const override {
    return "Composite Pattern Example";
  }
  void execute() override {
    problem::run();
    composite_pattern::run();
  }
};

REGISTER_EXAMPLE(CompositeExample);