
#ifndef CONTAINER_H_
#define CONTAINER_H_

/*************************************************************************
 * Container - Parameterizes its content and returns access to it.       *
 *************************************************************************/

template <typename Content_Type>
class Container
{
	private:

		Content_Type _content;

	public:

		Container(): _content() {}
		Container(const Content_Type & content): _content(content) {}
	    virtual ~Container() {}

		const Content_Type & content () const { return _content; }
		      Content_Type & content ()       { return _content; }

	    void content (const Content_Type & content) { _content = content; }
};

#endif /* CONTAINER_H_ */
