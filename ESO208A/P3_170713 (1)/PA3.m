fprintf("enter your choice\n 1.Least Square \n 2.Lagrange polynomial \n 3.Cubic Spline\n");
    meth=input('')'
    if meth==1
    fprintf("Give your no. of data and data points in a file named 'input2.txt'\n");
    fprintf("Please enter the degree of the polynomial for regression \n");
    m = input('');
    fid = fopen("input2.txt");
    line =fgetl(fid);
    n = sscanf(line, '%f ');
    B = zeros(n,2);
    for i=1:1:n
      line = fgetl(fid);
      B(i,1:1:2) = sscanf(line, '%f ');
    end;
    A=ones(m,m);

    for i=1:m+1
        k=i-1;
        for j=1:m+1
            [s]=sum(B,1,n,k+j-1);
            A(i,j)=s;
        end
    end
    R = ones(m+1,1);
    for i=1:m+1
        k=i-1;
      s2=0;
        for j=1:n
            s2=s2+(B(j,1).^k)*B(j,2);
        end
        R(i,1)=s2;
    end

    C = A\R;
    coeff=ones(m+1,1);
    k=m+1;
    for i=1:1:m+1
        coeff(i)= C(k);
        k=k-1;
    end
    
    syms x
    f=poly2sym(coeff);
    figure(1);
    fplot(f,[B(1,1),B(n,1)+0.1],'color','b'); hold on;
    plot(B(:,1),B(:,2),'x','color','r')
    hold off;
    grid

    for i=1:n
        yeval(i)= polyval(C,B(i,1));
    end

    [fbar] = sum(B,2,n,0)/n;
    s3=0;
    for i=1:n
        s3=s3+(B(i,2)-fbar).^2;
    end
    St=s3;
    s3=0;
    for i=1:n
        s3=s3+(B(i,2)-yeval(i)).^2;
    end
    Sr=s3;
    r = ((St-Sr)/St);

    fileId = fopen('output2.txt','w');
      fprintf(fileId,"Coefficient are :\n");
        fprintf(fileId,'%f \n',C);
        fprintf(fileId,'R-sq is : %f',r);
    fclose(fileId);

    
    end
    if meth==2
        fprintf("Give your no. of data and data points along with the the qwery abscissa value in a file named 'input1.txt'\n");
        fprintf("Press ENTER to continue\n\n");
        fid = fopen("input1.txt");
        line =fgetl(fid);
        n = sscanf(line, '%f ');
        B = zeros(n,2);
        for i=1:1:n
          line = fgetl(fid);
          B(i,1:1:2) = sscanf(line, '%f ');
        end;
        
        
            coeff = 0;
            for i = 1:n
                p=1;
                for j=1:n
                    if j~=i 
                    c = poly((B(j,1)))/(B(i,1)-B(j,1)) ;

                    p = conv(c, p);

                    end
                end
                term= B(i,2)*p;

                coeff = coeff +term;
            end         
            syms x
            f1=poly2sym(coeff);
            figure(2);
            fplot(f1,[B(1,1),B(n,1)+0.1],'color','b'); hold on;
            plot(B(:,1),B(:,2),'x','color','r')
            hold off;
            grid
            fileId = fopen('output2.txt','w');
            fprintf(fileId,"Coefficient are :\r\n");
            fprintf(fileId,'%f \r\n',coeff);
            fclose(fileId);
        end
        if meth==3
            fprintf("enter your choice \n 1.Natural \n 2.Not a Knot \n 3.Periodic \n 4.Clamped \n");
            way=input('');
            if way==1
          
                h=zeros(n-1,1);
                for i=1:n-1
                    h(i,1)=B(i+1,1)-B(i,1);
                end
                a=zeros(n,n);
                a(1,1)=1;
                a(n,n)=1;
                for i=2:n-1
                    a(i,i-1)=h(i-1,1);
                    a(i,i)=2*(h(i-1,1)+h(i,1));
                    a(i,i+1)=h(i,1);
                end
                b=zeros(n,1);
                g=zeros(n,1);
                for i=2:n
                    g(i,1) = (B(i,2)-B(i-1,2))/h(i-1,1);
                end
                for i=2:n-1
                    b(i,1) = 6*(g(i+1,1)-g(i,1));
                end
                sigma=inv(a)*b;
                A=zeros(n-1,1);
                B1=zeros(n-1,1);
                C=zeros(n-1,1);
                D=zeros(n-1,1);
                for i=1:n-1
                    A(i,1)=sigma(i+1,1)/(6*h(i,1));
                    B1(i,1)=sigma(i,1)/(6*h(i,1));
                    C(i,1)=(B(i+1,2)/h(i,1))-(sigma(i+1,1)*h(i,1)/6);
                    D(i,1)=(B(i,2)/h(i,1))-(sigma(i,1)*h(i,1)/6);
                end
                fileId = fopen('output2.txt','w');
            fprintf(fileId,"Coefficient are :\r\n");
                for i=1:n-1
                    coeff=0;
                    syms f(x)
                    f(x)=A(i,1).*((x-B(i,1)).^3)-B1(i,1).*((x-B(i+1,1)).^3)+C(i,1).*(x-B(i,1))-D(i,1).*(x-B(i+1,1));

                    coeff=collect(f(x));
                    
                    fprintf(fileId,'%s\r\n',char(coeff));
                    fprintf(fileId,"\r\n");
   
                       fplot(f,[B(i,1),B(i+1,1)+0.01],'color','b'); hold on;
                    

                end
                fclose(fileId);
                plot(B(:,1),B(:,2),'x','color','r');
                hold off;
            end
            
              if way==2
                        h=zeros(n-1,1);
                        for i=1:n-1
                            h(i,1)=B(i+1,1)-B(i,1);
                        end

                        a=zeros(n,n);
                        a(1,1)=h(2,1);
                        a(1,2)=-(h(1,1)+h(2,1));
                        a(1,3)=h(1,1);
                        a(n,n-2)=h(n-1,1);
                        a(n,n-1)=-(h(n-1,1)+h(n-2,1));
                        a(n,n)=h(n-2,1);
                        for i=2:n-1
                            a(i,i-1)=h(i-1,1);
                            a(i,i)=2*(h(i-1,1)+h(i-1,1));
                            a(i,i+1)=h(i-1,1);
                        end
                        b=zeros(n,1);
                        g=zeros(n,1);
                        for i=2:n
                            g(i,1) = (B(i,2)-B(i-1,2))/h(i-1,1);
                        end
                        for i=2:n-1
                            b(i,1) = 6*(g(i+1,1)-g(i,1));
                        end
                        sigma=inv(a)*b;
                        A=zeros(n-1,1);
                        B1=zeros(n-1,1);
                        C=zeros(n-1,1);
                        D=zeros(n-1,1);
                        for i=1:n-1
                            A(i,1)=sigma(i+1,1)/(6*h(i,1));
                            B1(i,1)=sigma(i,1)/(6*h(i,1));
                            C(i,1)=(B(i+1,2)/h(i,1))-(sigma(i+1,1)*h(i,1)/6);
                            D(i,1)=(B(i,2)/h(i,1))-(sigma(i,1)*h(i,1)/6);
                        end
                             fileId = fopen('output2.txt','w');
                     fprintf(fileId,"Coefficient are :\r\n");
                    for i=1:n-1
                    coeff=0;
                    syms f(x)
                    f(x)=A(i,1).*((x-B(i,1)).^3)-B1(i,1).*((x-B(i+1,1)).^3)+C(i,1).*(x-B(i,1))-D(i,1).*(x-B(i+1,1));
%   
                    coeff=collect(f(x));
                    
                    fprintf(fileId,'%s\r\n',char(coeff));
                    fprintf(fileId,"\r\n");
   
                       fplot(f,[B(i,1),B(i+1,1)+0.01],'color','b'); hold on;
                    

                end
                fclose(fileId);
                plot(B(:,1),B(:,2),'x','color','r');
                hold off;
                  end
              end
              if way==3
                        
                        h=zeros(n-1,1);
                        for i=1:n-1
                            h(i,1)=B(i+1,1)-B(i,1);
                        end

                        a=zeros(n,n);
                        a(1,1)=2*h(1,1);
                        a(1,2)=h(1,1);
                        a(1,n-1)=h(n-1,1);
                        a(1,n)=2*h(n-1,1);
                        a(n,1)=1;
                        a(n,n)=-1;
                        for i=2:n-1
                            a(i,i-1)=h(i-1,1);
                            a(i,i)=2*(h(i-1,1)+h(i,1));
                            a(i,i+1)=h(i,1);
                        end
                        b=zeros(n,1);
                        g=zeros(n,1);
                        for i=2:n
                            g(i,1) = (B(i,2)-B(i-1,2))/h(i-1,1);
                        end
                        for i=2:n-1
                            b(i,1) = 6*(g(i+1,1)-g(i,1));
                        end
                        b(1)=-6*((B(n,2)-B(n-1,2))/h(n-1,1)) + (6*(B(2,2) - (B(1,2)))/h(1,1));
                        sigma=inv(a)*b;
                        A=zeros(n-1,1);
                        B1=zeros(n-1,1);
                        C=zeros(n-1,1);
                        D=zeros(n-1,1);
                        for i=1:n-1
                            A(i,1)=sigma(i+1,1)/(6*h(i,1));
                            B1(i,1)=sigma(i,1)/(6*h(i,1));
                            C(i,1)=(B(i+1,2)/h(i,1))-(sigma(i+1,1)*h(i,1)/6);
                            D(i,1)=(B(i,2)/h(i,1))-(sigma(i,1)*h(i,1)/6);
                        end
                             fileId = fopen('output2.txt','w');
                     fprintf(fileId,"Coefficient are :\r\n");
                    for i=1:n-1
                    coeff=0;
                    syms f(x)
                    f(x)=A(i,1).*((x-B(i,1)).^3)-B1(i,1).*((x-B(i+1,1)).^3)+C(i,1).*(x-B(i,1))-D(i,1).*(x-B(i+1,1));
 
                    coeff=collect(f(x));
                    
                    fprintf(fileId,'%s\r\n',char(coeff));
                    fprintf(fileId,"\r\n");
   
                       fplot(f,[B(i,1),B(i+1,1)+0.01],'color','b'); hold on;
                    

                end
                fclose(fileId);
                plot(B(:,1),B(:,2),'x','color','r');
                hold off;
                  end
              
              if way==4
                    fprintf("enter first derivative value \n")
                    s1=input('');
                    fprintf("enter second derivative value \n")
                    s2=input('');
                    h=zeros(n-1,1);
                    for i=1:n-1
                        h(i,1)=B(i+1,1)-B(i,1);
                    end
                    a=zeros(n,n);
                    a(1,1)=2*h(1,1);
                    a(1,2)=h(1,1);
                    a(n,n)=2*h(n-1,1);
                    a(n,n-1)=h(n-1,1);
                    for i=2:n-1
                        a(i,i-1)=h(i-1,1);
                        a(i,i)=2*(h(i-1,1)+h(i,1));
                        a(i,i+1)=h(i,1);
                    end
                    b=zeros(n,1);
                    g=zeros(n,1);
                    for i=2:n
                        g(i,1) = (B(i,2)-B(i-1,2))/h(i-1,1);
                    end
                    for i=2:n-1
                        b(i,1) = 6*(g(i+1,1)-g(i,1));
                    end
                    b(1,1)=6*(((B(2,2)-B(1,2))/h(1,1))-s1);
                    b(n,1)=6*(((B(n-1,2)-B(n,2))/h(n-1,1)) + s2);
                    sigma=inv(a)*b;
                    A=zeros(n-1,1);
                    B1=zeros(n-1,1);
                    C=zeros(n-1,1);
                    D=zeros(n-1,1);
                    for i=1:n-1
                        A(i,1)=sigma(i+1,1)/(6*h(i,1));
                        B1(i,1)=sigma(i,1)/(6*h(i,1));
                        C(i,1)=(B(i+1,2)/h(i,1))-(sigma(i+1,1)*h(i,1)/6);
                        D(i,1)=(B(i,2)/h(i,1))-(sigma(i,1)*h(i,1)/6);
                    end
                    fileId = fopen('output2.txt','w');
                     fprintf(fileId,"Coefficient are :\r\n");
                    for i=1:n-1
                    coeff=0;
                    syms f(x)
                    f(x)=A(i,1).*((x-B(i,1)).^3)-B1(i,1).*((x-B(i+1,1)).^3)+C(i,1).*(x-B(i,1))-D(i,1).*(x-B(i+1,1));
%   
                    coeff=collect(f(x));
                    
                    fprintf(fileId,'%s\r\n',char(coeff));
                    fprintf(fileId,"\r\n");
   
                       fplot(f,[B(i,1),B(i+1,1)+0.01],'color','b'); hold on;
                    

                end
                fclose(fileId);
                plot(B(:,1),B(:,2),'x','color','r');
                hold off;
                  end
              
              
        
       
    
    
    function [s] = sum(B,k,n,p)
        s=0;
        for i=1:n
            s=s+(B(i,k).^p);
        end
    end
