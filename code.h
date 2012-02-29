class PUSH_INT : public OpCode
{
public:
	PUSH_INT(int i):x(new Variable(i),0){}
	RC::RETURNCODE Execute(Environment &env)
	{
		env.push(x);
		return RC::NONE;
	}
	void dump(){std::printf("PUSH %d\n", x.get()->toInt());}
	void write(bytecode &b){b.push(MNEMONIC::PUSH_INT);int w = x.get()->toInt();b.push(&w, sizeof(w));}
private:
	rsv x;	// �ꉞ�A�萔�ɑ΂��Čv�Z�o���Ă��܂��Ƃ�����肪�����Ă��邪�H
	// for (int i = 0; i < ++4; i++)
	// ����͈ȑO�Ȃ�i < 5�Ɠ�����������
	// ���̎������Ɩ������[�v�˓��ł���
};
class PUSH_HEX : public OpCode
{
public:
	PUSH_HEX(hex l):x(new Variable(new vHex(l)),0){}
	RC::RETURNCODE Execute(Environment &env)
	{
		env.push(x);
		return RC::NONE;
	}
	void dump(){std::printf("PUSH %X\n", x.get()->toInt());}
	void write(bytecode &b){b.push(MNEMONIC::PUSH_HEX);hex w = x.get()->toInt();b.push(&w, sizeof(w));}
private:
	rsv x;
};
class PUSH_FLOAT : public OpCode
{
public:
	PUSH_FLOAT(double d):x(new Variable(d),0){}
	RC::RETURNCODE Execute(Environment &env)
	{
		env.push(x);
		return RC::NONE;
	}
	void dump(){std::printf("PUSH %f\n", x.get()->toDouble());}
	void write(bytecode &b){b.push(MNEMONIC::PUSH_FLOAT);double w = x.get()->toDouble();b.push(&w, sizeof(w));}
private:
	rsv x;
};
class PUSH_STRING : public OpCode
{
public:
	PUSH_STRING(string &s):x(new Variable(s),0){}
	RC::RETURNCODE Execute(Environment &env)
	{
		env.push(x);
		return RC::NONE;
	}
	void dump(){std::printf("PUSH %s\n", x.get()->toString().c_str());}
	void write(bytecode &b){b.push(MNEMONIC::PUSH_STRING);string w = x.get()->toString();b.push(w.c_str(), w.length()+1);}
private:
	rsv x;
};
class POP : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		env.pop();
		return RC::NONE;
	}
	void dump(){std::printf("POP\n");}
	void write(bytecode &b){b.push(MNEMONIC::POP);}
};
class PUSH_NULL : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		env.push(x);
		return RC::NONE;
	}
	void dump(){std::printf("PUSH NULL\n");}
	void write(bytecode &b){b.push(MNEMONIC::PUSH_NULL);}
private:
	rsv x;
};
class POP_VARIABLE : public OpCode
{
public:
	POP_VARIABLE(string &s)	{name = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.getVariable(name);
		v = env.pop();
		return RC::NONE;
	}
	void dump(){std::printf("POP VARIABLE %s\n", name.c_str());}
private:
	string name;
};

class SUBSTITUTION : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable r = env.pop();
		variable l = env.pop();
		env.push(l.substitution(r));
		return RC::NONE;
	}
	void dump(){std::printf("SUBSTITUTION\n");}
	void write(bytecode &b){b.push(MNEMONIC::SUBSTITUTION);}
};
class ASSIGNMENT : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable r = env.pop();
		variable l = env.pop();
		env.push(l.assignment(r));
		return RC::NONE;
	}
	void dump(){std::printf("ASSIGNMENT\n");}
	void write(bytecode &b){b.push(MNEMONIC::ASSIGNMENT);}
};
class ARGUMENT : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable l = env.pop();
		variable r = env.pop();
		l.substitution(r);
		return RC::NONE;
	}
	void dump(){std::printf("ARGUMENT\n");}
	void write(bytecode &b){b.push(MNEMONIC::ARGUMENT);}
};


class PLUS : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		return RC::NONE;
	}
	void dump(){std::printf("PLUS\n");}
	void write(bytecode &b){b.push(MNEMONIC::PLUS);}
};
class MINUS : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		env.push(-v);
		return RC::NONE;
	}
	void dump(){std::printf("MINUS\n");}
	void write(bytecode &b){b.push(MNEMONIC::MINUS);}
};
class NOT : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		variable x = !(bool)v;
		env.push(x);
		return RC::NONE;
	}
	void dump(){std::printf("NOT\n");}
	void write(bytecode &b){b.push(MNEMONIC::NOT);}
};
class COMPL : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		variable x(~(int)v);
		env.push(x);
		return RC::NONE;
	}
	void dump(){std::printf("COMPL\n");}
	void write(bytecode &b){b.push(MNEMONIC::COMPL);}
};
class INC : public OpCode	// ��u
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		variable c = v;	// �l���R�s�[
		env.push(c);
		v += 1;
		return RC::NONE;
	}
	void dump(){std::printf("INC\n");}
	void write(bytecode &b){b.push(MNEMONIC::INC);}
};
class PINC : public OpCode	// �O�u
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		env.push(v += 1);
		return RC::NONE;
	}
	void dump(){std::printf("PINC\n");}
	void write(bytecode &b){b.push(MNEMONIC::PINC);}
};
class DEC : public OpCode	// ��u
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		variable c = v;	// �l���R�s�[
		env.push(c);
		v -= 1;
		return RC::NONE;
	}
	void dump(){std::printf("DEC\n");}
	void write(bytecode &b){b.push(MNEMONIC::DEC);}
};
class PDEC : public OpCode	// �O�u
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		env.push(v -= 1);
		return RC::NONE;
	}
	void dump(){std::printf("PDEC\n");}
	void write(bytecode &b){b.push(MNEMONIC::PDEC);}
};
class DEREF : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		env.push(*v);
		return RC::NONE;
	}
	void dump(){std::printf("DEREF\n");}
	void write(bytecode &b){b.push(MNEMONIC::DEREF);}
};
class REF : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		env.push(v.pointer());
		return RC::NONE;
	}
	void dump(){std::printf("REF\n");}
	void write(bytecode &b){b.push(MNEMONIC::REF);}
};

#define OOC(n,o) class n:public OpCode{public:RC::RETURNCODE Execute(Environment&env){variable r=env.pop();variable l=env.pop();env.push(l o r);return RC::NONE;}void dump(){std::printf(#n"\n");}void write(bytecode &b){b.push(MNEMONIC::n);}}
OOC(SADD,+=);
OOC(SSUB,-=);
OOC(SMUL,*=);
OOC(SDIV,/=);
OOC(SMOD,%=);
OOC(SAND,&=);
OOC(SOR,|=);
OOC(SXOR,^=);
OOC(SSHL,<<=);
OOC(SSHR,>>=);
//OOC(MOV,=);
#undef OOC
#define OOC(n,o) class n:public OpCode{public:RC::RETURNCODE Execute(Environment&env){variable r=env.pop();variable l=env.pop();variable x(l o r);env.push(x);return RC::NONE;}void dump(){std::printf(#n"\n");}void write(bytecode &b){b.push(MNEMONIC::n);}}
OOC(ADD,+);
OOC(SUB,-);
OOC(MUL,*);
OOC(DIV,/);
OOC(MOD,%);
OOC(AND,&);
OOC(OR,|);
OOC(XOR,^);
OOC(SHL,<<);
OOC(SHR,>>);
OOC(EQ,==);
OOC(NEQ,!=);
OOC(LE,<=);
OOC(GE,>=);
OOC(LT,<);
OOC(GT,>);
#undef OOC

class VARIABLE : public OpCode
{
public:
	VARIABLE(string &s)	{name = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.getVariable(name);
		env.push(v);
		return RC::NONE;
	}
	void dump(){std::printf("VARIABLE %s\n", name.c_str());}
	void write(bytecode &b){b.push(MNEMONIC::VARIABLE);b.push(name.c_str(), name.length()+1);}
private:
	string name;
};

class BAND : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable r = env.pop();
		variable l = env.pop();
		variable v((bool)l && (bool)r);
		env.push(v);
		return RC::NONE;
	}
	void dump(){std::printf("BAND\n");}
	void write(bytecode &b){b.push(MNEMONIC::BAND);}
};
class BOR : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable r = env.pop();
		variable l = env.pop();
		variable v((bool)l || (bool)r);
		env.push(v);
		return RC::NONE;
	}
	void dump(){std::printf("BOR\n");}
	void write(bytecode &b){b.push(MNEMONIC::BOR);}
};



// f = function(x){return x+1;};	�݂����Ȃ̗p
class PUSH_CODE : public OpCode
{
	RC::RETURNCODE Execute(Environment &env)
	{
		return RC::NONE;
	}
private:
	Code *c;
};


class JMP : public OpCode
{
public:
	JMP(int i)	{j = i;}
	void set(int s){j = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		env.Jump(j);
		return RC::NONE;
	}
	void dump(){std::printf("JMP %d\n", j);}
	void write(bytecode &b){b.push(MNEMONIC::JMP);b.push(&j, sizeof(j));}
private:
	int j;
};
class JT : public OpCode
{
public:
	JT(int i)	{j = i;}
	void set(int s){j = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		if ((bool)v)
			env.Jump(j);
		return RC::NONE;
	}
	void dump(){std::printf("JT %d\n", j);}
	void write(bytecode &b){b.push(MNEMONIC::JT);b.push(&j, sizeof(j));}
private:
	int j;
};
class JF : public OpCode
{
public:
	JF(int i)	{j = i;}
	void set(int s){j = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		if (!(bool)v)
			env.Jump(j);
		return RC::NONE;
	}
	void dump(){std::printf("JF %d\n", j);}
	void write(bytecode &b){b.push(MNEMONIC::JF);b.push(&j, sizeof(j));}
private:
	int j;
};
class JR : public OpCode		// ���΃W�����v�A�s�͎��s���ɂ͎����w���Ă��邱�Ƃɒ���
{
public:
	JR(int i)	{j = i;}
	void set(int s){j = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		env.RJump(j);
		return RC::NONE;
	}
	void dump(){std::printf("JR %d\n", j);}
	void write(bytecode &b){b.push(MNEMONIC::JR);b.push(&j, sizeof(j));}
private:
	int j;
};
class JRT : public OpCode
{
public:
	JRT(int i)	{j = i;}
	void set(int s){j = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		if ((bool)v)
			env.RJump(j);
		return RC::NONE;
	}
	void dump(){std::printf("JRT %d\n", j);}
	void write(bytecode &b){b.push(MNEMONIC::JRT);b.push(&j, sizeof(j));}
private:
	int j;
};
class JRF : public OpCode
{
public:
	JRF(int i)	{j = i;}
	void set(int s){j = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		if (!(bool)v)
			env.RJump(j);
		return RC::NONE;
	}
	void dump(){std::printf("JRF %d\n", j);}
	void write(bytecode &b){b.push(MNEMONIC::JRF);b.push(&j, sizeof(j));}
private:
	int j;
};

class LIST : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable r = env.pop();
		variable l = env.pop();
		if (l.type(variable::RARRAY))
		{
			l.push(r);
			env.push(l);
		}
		else
		{
			variable ref(variable::RARRAY);
			ref.push(l);
			ref.push(r);
			env.push(ref);
		}
		return RC::NONE;
	}
	void dump(){std::printf("LIST\n");}
	void write(bytecode &b){b.push(MNEMONIC::LIST);}
};

class PARENTHESES : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		variable r(variable::RARRAY);
		r.push(v);
		env.push(r);
		return RC::NONE;
	}
	void dump(){std::printf("PARENTHESES\n");}
	void write(bytecode &b){b.push(MNEMONIC::PARENTHESES);}
};

class CALL : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable r = env.pop();
		variable v = env.pop();
		env.push(r);
		if (env.getNext() == MNEMONIC::RETURN)
			env.Return();	// �����œK��
		v.prepare(env);
		return RC::CALL;
	}
	void dump(){std::printf("CALL\n");}
	void write(bytecode &b){b.push(MNEMONIC::CALL);}
};

class RETURN : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		env.Return();
		return RC::RETURN;
	}
	MNEMONIC::mnemonic get()	{return MNEMONIC::RETURN;}
	void dump(){std::printf("RETURN\n");}
	void write(bytecode &b){b.push(MNEMONIC::RETURN);}
};
class BREAK : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		env.Break();
		return RC::BREAK;
	}
	void dump(){std::printf("BREAK\n");}
	void write(bytecode &b){b.push(MNEMONIC::BREAK);}
};
class CONTINUE : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		env.Continue();
		return RC::CONTINUE;
	}
	void dump(){std::printf("CONTINUE\n");}
	void write(bytecode &b){b.push(MNEMONIC::CONTINUE);}
};
class YIELD : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
//		env.Yield();	// ���Ă��邱�ƂȂ��ˁH
		return RC::YIELD;
	}
	void dump(){std::printf("YIELD\n");}
	void write(bytecode &b){b.push(MNEMONIC::YIELD);}
};
class GOTO : public OpCode
{
public:
	GOTO(string &s)	{label = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		env.Goto(label);
		return RC::GOTO;
	}
	void dump(){std::printf("GOTO %s\n", label.c_str());}
	void write(bytecode &b){b.push(MNEMONIC::VARIABLE);b.push(label.c_str(), label.length()+1);}
private:
	string label;
};

class SCOPE : public OpCode
{
public:
	SCOPE(variable &v)	{statement = v.getcode()->inc();}
	~SCOPE()	{statement->finalize();}
	RC::RETURNCODE Execute(Environment &env)
	{
		Scope *s = new AnonymousScope(statement);
		env.addScope(s);
		return RC::SCOPE;
	}
	void dump(){std::printf("SCOPE\n");statement->dump();std::printf("SCOPE END\n");}
	void write(bytecode &b){b.push(MNEMONIC::SCOPE);statement->write(b);}
protected:
	Code *statement;
};
class LOOP : public OpCode
{
public:
	LOOP(variable &v, int l)	{statement = v.getcode()->inc();cline = l;}
	~LOOP()	{statement->finalize();}
	RC::RETURNCODE Execute(Environment &env)
	{
		Scope *s = new LoopScope(statement, cline);
		env.addScope(s);
		return RC::LOOP;
	}
	void dump(){std::printf("LOOP\n");statement->dump();std::printf("LOOP END\n");}
	void write(bytecode &b){b.push(MNEMONIC::LOOP);b.push(&cline, sizeof(cline));statement->write(b);}
private:
	Code *statement;
	int cline;	// continue line
};
#ifdef PSL_DEBUG
class IF : public SCOPE
{
public:
	IF(variable &v):SCOPE(v){}
	RC::RETURNCODE Execute(Environment &env)
	{
		Scope *s = new AnonymousScope(statement);
		env.addScope(s);
		return RC::IF;
	}
	void dump(){std::printf("IF\n");statement->dump();std::printf("IF END\n");}
	void write(bytecode &b){b.push(MNEMONIC::IF);statement->write(b);}
};	// ����SCOPE�Ɠ��������Adump��������if���ł��邱�Ƃ����m�ɂȂ邮�炢�A�f�o�b�O�p�ɂ͂����Ă���������
#endif

class LOCAL : public OpCode
{
public:
	LOCAL(string &s)	{name = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		env.addLocal(name, v);
		return RC::NONE;
	}
	void dump(){std::printf("LOCAL %s\n", name.c_str());}
	void write(bytecode &b){b.push(MNEMONIC::LOCAL);b.push(name.c_str(), name.length()+1);}
private:
	string name;
};
class GLOBAL : public OpCode
{
public:
	GLOBAL(string &s)	{name = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		env.addGlobal(name, v);
		return RC::NONE;
	}
	void dump(){std::printf("GLOBAL %s\n", name.c_str());}
	void write(bytecode &b){b.push(MNEMONIC::GLOBAL);b.push(name.c_str(), name.length()+1);}
private:
	string name;
};
class STATIC : public OpCode
{
public:
	STATIC(string &s)	{name = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		env.addStatic(name, v);
		return RC::NONE;
	}
	void dump(){std::printf("STATIC %s\n", name.c_str());}
	void write(bytecode &b){b.push(MNEMONIC::STATIC);b.push(name.c_str(), name.length()+1);}
private:
	string name;
};

class DECLARATION : public OpCode
{
public:
	DECLARATION(string &s)	{name = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		env.Declaration(name, v);
		return RC::NONE;
	}
	void dump(){std::printf("DECLARATION %s\n", name.c_str());}
	void write(bytecode &b){b.push(MNEMONIC::DECLARATION);b.push(name.c_str(), name.length()+1);}
private:
	string name;
};

class INSTANCE : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		v.prepareInstance(env);
		return RC::CALL;
	}
	void dump(){std::printf("INSTANCE\n");}
	void write(bytecode &b){b.push(MNEMONIC::INSTANCE);}
};
/*
class LABEL : public OpCode
{
public:
	LABEL(string &s)	{name = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		// �Ȃɂ����Ȃ�
		return RC::NONE;
	}
	void dump(){std::printf("LABEL %s\n", name.c_str());}
	void write(bytecode &b){b.push(MNEMONIC::LABEL);b.push(name.c_str(), name.length()+1);}
private:
	string name;
};
*/


class MEMBER : public OpCode
{
public:
	MEMBER(string &s)	{name = s;}
	RC::RETURNCODE Execute(Environment &env)
	{
		variable v = env.pop();
		variable x = v[name];
		env.push(x);
		return RC::NONE;
	}
	void dump(){std::printf("MEMBER %s\n", name.c_str());}
	void write(bytecode &b){b.push(MNEMONIC::MEMBER);b.push(name.c_str(), name.length()+1);}
private:
	string name;
};
class INDEX : public OpCode
{
public:
	RC::RETURNCODE Execute(Environment &env)
	{
		variable i = env.pop();
		variable v = env.pop();
		env.push(v[i]);
		return RC::NONE;
	}
	void dump(){std::printf("INDEX\n");}
	void write(bytecode &b){b.push(MNEMONIC::INDEX);}
};