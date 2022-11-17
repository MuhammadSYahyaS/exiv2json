#include <iostream>
#include <iomanip>
#include <cassert>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <exiv2/exiv2.hpp>

namespace pt = boost::property_tree;

int main(int argc, const char **argv)
{
	try
	{
		if (argc != 2)
		{
			std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
			return 1;
		}
		Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(argv[1]);
		assert(image.get() != 0);
		image->readMetadata();

		std::string output_path_str = std::string(argv[1]) + ".json";
		std::cout << " --> " << output_path_str << std::endl;
		pt::ptree tree;
		for (const Exiv2::Exifdatum d : image->exifData())
		{
			tree.put(d.key(), d.value());
		}
		for (const Exiv2::Xmpdatum d : image->xmpData())
		{
			tree.put(d.key(), d.value());
		}
		for (const Exiv2::Iptcdatum d : image->iptcData())
		{
			tree.put(d.key(), d.value());
		}
		pt::json_parser::write_json(output_path_str, tree);

		std::cout << "Done!" << std::endl;
		return 0;
	}
	catch (Exiv2::AnyError &e)
	{
		std::cout << "Caught Exiv2 exception '" << e << "'\n";
		return -1;
	}
	catch (...)
	{
		// Any other exception - just in case
		std::cout << "Argh - we got an exception" << std::endl;
		std::exception_ptr p = std::current_exception();
		std::clog << (p ? p.__cxa_exception_type()->name() : "null") << std::endl;
		return 1;
	}
}
