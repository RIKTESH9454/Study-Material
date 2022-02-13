str = input('wether equation is polynomial:','s');
if str == 'N'
    str = input('Give a nonlinear equation in x:','s');
    f= inline(str);
    fprintf('Enter the method  :\n1: Bisection\n2: False-position\n3: Fixed-Point\n4: Newton-Raphson\n5: Secant\n');
    meth = input('');
    if meth == 1,
      fprintf('Enter the lower bracket for the root\n');
      x1 = input('');
      fprintf('Enter the upper bracket for the root\n');
      x2 = input('');
      fprintf('Maximum iterations :\n');
      maxiter=input('');
      fprintf('Maximum relative approximate error:\n')
      maxerror = input('');
      conv=input('enter convergence criteria for the function value : ');
      xrange = (x1-(x2-x1)):0.1:(x2+(x2-x1));
      figure;
      for val=1:1:size(xrange,2)
        y(val) = f(xrange(val));
      end;
      plot(xrange,y)
      xlabel('x');
      ylabel('f(x)');
      y1=f(x1);
      y2=f(x2);
      error(1)=100;
      iter=0;
      ymid=1;
      lastxmid=111;
      flag=3;
      for i=1:maxiter


        xmid=(x1+x2)/2;
        ymid=f(xmid);
        if (ymid*y1<0)
          y2=ymid;
          x2=xmid;
        else
          x1=xmid;
          y1=ymid;
        end;

          error(iter+1)=abs((lastxmid-xmid)*100/xmid);
          if error(iter+1)<maxerror
              flag=1;
              break;
          end;
          if abs(ymid)<conv
              flag=2;
              break;
          end;
          lastxmid=xmid;
          iter=iter+1;

      end;  
      xmid
      if flag==1
          disp('stopping criteria is convergence criterion for relative approximate errors in successive iterations');
      elseif flag==2
          disp('stopping criteria is convergence criteria for the function value');
      else
          disp('stopping criteria is number of iterations');
      end;

      iterations = 2:1:iter;
      error =error(1,2:iter);
      figure;
      plot(iterations, error)
      xlabel('Number of iterations');
      ylabel('Relative approximate error');

    end;

    if meth == 2,
      fprintf('Enter the lower bracket for the root\n');
      x1 = input('');
      fprintf('Enter the upper bracket for the root\n');
      x2 = input('');


      fprintf('Maximum iterations:\n');
      maxiter=input('');
      fprintf('Maximum relative approximate error:\n')
      maxerror = input('');
      conv=input('enter convergence criteria for the function value : \n');
      xrange = (x1-(x2-x1)):0.1:(x2+(x2-x1));
      figure;
      for val=1:1:size(xrange,2)
        y(val) = f(xrange(val));
      end;
      plot(xrange,y)
      xlabel('x');
      ylabel('f(x)');
      y1=f(x1);
      y2=f(x2);
      error(1)=100;
      iter=0;
      ymid=1;
      lastxmid=111;
      flag=3;
      for i=1:maxiter

        xmid=x2 - y2*((x2-x1)/(y2-y1));
        ymid=f(xmid);
        if (ymid*y1<0)
          y2=ymid;
          x2=xmid;


        else
          x1=xmid;
          y1=ymid;

        end;
        error(iter+1)=abs((lastxmid-xmid)*100/xmid);
         if error(iter+1)<maxerror
              flag=1;
              break;
          end;
          if abs(ymid)<conv
              flag=2;
              break;
          end;
          lastxmid=xmid;
          iter= iter + 1;

      end;  
      xmid
      if flag==1
          disp('stopping criteria is convergence criterion for relative approximate errors in successive iterations');
      elseif flag==2
          disp('stopping criteria is convergence criteria for the function value');
      else
          disp('stopping criteria is number of iterations');
      end;
      iterations = 2:1:iter;
      error =error(1,2:iter);
      figure;
      plot(iterations, error)
      xlabel('Number of iterations');
      ylabel('Relative approximate error');

    end;


    if meth == 3,
      str1 = input('Enter g(x):','s');
      g = inline(str1);
      fprintf('Enter the initial guess\n');
      x1 = input('');
      fprintf('Maximum iteration:\n');
      maxiter=input('');
      fprintf('Maximum relative approximate error :\n')
      maxerror = input('');
      conv=input('enter convergence criteria for the function value : \n');
      if x1>=0
        xrange = (-x1-10):0.1:(2*x1+10);
      else
        xrange = (-x1+10):-0.1:(2*x1-10);
      end;
      figure;
      for val=1:1:size(xrange,2)
        y(val) = f(xrange(val));
      end;
      plot(xrange,y)
      xlabel('x');
      ylabel('f(x)');
      error(1)=200;
      iter=0;
      flag=3;
      xmid=x1;
      lastxmid =x1;
      for i=1:maxiter

        ymid=g(xmid);
        xmid=ymid;
        error(iter+1)=abs((lastxmid-xmid)*100/xmid);
         if error(iter+1)<maxerror
              flag=1;
              break;
          end;
          if abs(ymid)<conv
              flag=2;
              break;
          end;
        lastxmid=xmid;
        iter= iter + 1;
      end;  
      xmid
      if flag==1
          disp('stopping criteria is convergence criterion for relative approximate errors in successive iterations');
      elseif flag==2
          disp('stopping criteria is convergence criteria for the function value');
      else
          disp('stopping criteria is number of iterations');
      end;
      iterations = 1:1:iter-1;
      error =error(1,1:iter-1);
      figure;
      plot(iterations, error)
      xlabel('Number of iterations');
      ylabel('Relative approximate error');

    end;


    if meth == 4,
      str1 = input('Enter derivative of f(x):','s');
      g = inline(str1);
      fprintf('Enter the initial guess\n');
      x1 = input('');

      fprintf('Maximum iterations :\n');
      maxiter=input('');
      fprintf('Maximum relative approximate error:\n')
      maxerror = input('');
      conv=input('enter convergence criteria for the function value : \n');
      if x1>=0
        xrange = (-x1-5):0.1:(2*x1+5);
      else
        xrange = (-x1+5):-0.1:(2*x1-5);
      end;
      figure;
      for val=1:1:size(xrange,2)
        y(val) = f(xrange(val));
      end;
      plot(xrange,y)
      xlabel('x');
      ylabel('f(x)');
      error(1)=100;
      iter=0;
      flag=3;
      xmid=x1;
      lastxmid =x1;
      for i=1:maxiter

        ymid=f(xmid);
        xmid=xmid - (ymid/g(xmid));
        error(iter+1)=abs((lastxmid-xmid)*100/xmid);
         if error(iter+1)<maxerror
              flag=1;
              break;
          end;
          if abs(ymid)<conv
              flag=2;
              break;
          end;
        lastxmid=xmid;
        iter= iter + 1;
      end;  
      xmid
      if flag==1
          disp('stopping criteria is convergence criterion for relative approximate errors in successive iterations');
      elseif flag==2
          disp('stopping criteria is convergence criteria for the function value');
      else
          disp('stopping criteria is number of iterations');
      end;
      iterations = 1:1:iter-1;
      error =error(1,1:iter-1);
      figure;
      plot(iterations, error)
      xlabel('Number of iterations');
      ylabel('Relative approximate error');

    end;

    if meth == 5,
      fprintf('Enter the smaller point\n');
      x1 = input('');
      fprintf('Enter the larger point\n');
      x2 = input('');
      fprintf('Maximum iterations :\n');
      maxiter=input('');
      fprintf('Maximum relative approximate error :\n')
      maxerror = input('');
      conv=input('enter convergence criteria for the function value : \n');
      xrange = (x1-4*(x2-x1)):0.1:(x2+4*(x2-x1));
      figure;
      for val=1:1:size(xrange,2)
        y(val) = f(xrange(val));
      end;
      plot(xrange,y)
      xlabel('x');
      ylabel('f(x)');
      error(1)=100;
      iter=0;
      flag=3;
      y1=f(x1);
      y2=f(x2);
      xmid=x1;
      lastxmid =x1;
      for i=1:maxiter

        xmid=x2 - y2*((x2-x1)/(y2-y1));
        ymid=f(xmid);
        if y1>y2
          y1=ymid;
          x1=xmid;
        else
          y2=ymid;
          x2=xmid;
        end;

        error(iter+1)=abs((lastxmid-xmid)*100/xmid);
         if error(iter+1)<maxerror
              flag=1;
              break;
          end;
          if abs(ymid)<conv
              flag=2;
              break;
          end;
        lastxmid=xmid;
        iter= iter + 1;
      end;  
      xmid
      if flag==1
          disp('stopping criteria is convergence criterion for relative approximate errors in successive iterations');
      elseif flag==2
          disp('stopping criteria is convergence criteria for the function value');
      else
          disp('stopping criteria is number of iterations');
      end;
      iterations = 2:1:iter;
      error =error(1,2:iter);
      figure;
      plot(iterations, error)
      xlabel('Number of iterations');
      ylabel('Relative approximate error');

    end;
else
        fprintf('Enter the degree of your polynomial\n');
    n = input('');
    fprintf('Enter the coeffiecient from n to 0 for muller and from 0 to n for bairstow :\n');
    for k=1:1:n+1

      coeff(k)=input('');
      fprintf('\n');
    end;
    fprintf('Enter the method you want to use for :\n1: Muller\n2: Bairstow\n');
    meth = input('');
    if meth == 1,

        syms x
        f=poly2sym(coeff);
      fprintf('Enter the smaller point\n');
      x3 = input('');
      fprintf('Enter the middle point\n');
      x2 = input('');
      fprintf('Enter the larger point\n');
      x1 = input('');
      fprintf('Maximum iterations :\n');
      maxiter=input('');
      fprintf('Maximum relative approximate error :\n')
      maxerror = input('');
      ezplot(f);

      v(1) = x1;
             v(2) = x2;
             v(3) = x3;
             flag = 1;
             for i=1:maxiter
                 h0 = v(i+1) - v(i);
                 h1 = v(i+2) - v(i+1);
    %              disp(polyval(poly, val(i)));
    %              disp(polyval(poly, val(i+1)));
    %              disp(polyval(poly, val(i+2)));
                 delta_1 = (polyval(coeff, v(i+1)) - polyval(coeff, v(i)))/h0;
                 delta_2 = (polyval(coeff, v(i+2)) - polyval(coeff, v(i+1)))/h1;
                 a = (delta_2 - delta_1)/(h0 + h1);
                 b = a*h1 + delta_2;
                 c = polyval(coeff, v(i+2));
                 v(i+3) = v(i+2) - ((2*c)/(b + sqrt(b^(2) - 4*a*c)));
                 if(abs(((v(i+3) - v(i+2))/(v(i+2)))) <= maxerror)
                     flag = 2;
                     break;
                 end
             end
             fprintf('Value of root: %s\n', v(i+3));
             if flag == 1
                disp('Stopping criteria is number of iterations');
             else
                disp('Stopping criteria is tolerance');
             end

    end;
    if meth == 2,

      syms x
        f=poly2sym(coeff);
      fprintf('Enter s\n');
      s = input('');
      fprintf('Enter r\n');
      r = input('');
      fprintf('Maximum iterations you :\n');
      maxiter=input('');
      fprintf('Maximum relative approximate error :\n')
      maxerror = input('');
       ezplot(f);
      error=100;
      iter=0;
      d=zeros(1,n+1);
      delta=zeros(1,n);
      while (error>maxerror) && (iter<maxiter)
        d(1,n+1)=coeff(1,n+1);
        d(1,n)=coeff(1,n)+r*d(1,n+1);
        for i=n-1:-1:1
          d(1,i) = coeff(1,i)+r*d(1,i+1)+s*d(1,i+2);
        end;
        delta(1,n) = d(1,n+1);
        delta(1,n-1) = d(1,n)+r*delta(1,n);
        for j=n-2:-1:1
          delta(1,j) = d(1,j+1)+r*delta(1,j+1)+s*delta(1,j+2);
        end;
        delta_alpha0 = (delta(1,1)*d(1,2)-delta(1,2)*d(1,1))/(delta(1,2)*delta(1,2)-delta(1,1)*delta(1,3));
        delta_alpha1 = (delta(1,3)*d(1,1)-delta(1,2)*d(1,2))/(delta(1,2)*delta(1,2)-delta(1,1)*delta(1,3));
        s=s+delta_alpha0;
        r=r+delta_alpha1;
        if abs(delta_alpha0) > abs(delta_alpha1)
          error = delta_alpha1/r;
        else
          error = delta_alpha0/s;
        end;   
        error = abs(error)*100;
        iter= iter + 1;
        flag=1;
      end;  
      root1 = 0.5*(r+sqrt(r*r+4*s));
      root2 = 0.5*(r-sqrt(r*r+4*s));
      root1
      root2
    end;
end;
clear
